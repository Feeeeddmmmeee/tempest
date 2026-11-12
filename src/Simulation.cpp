#include "Simulation.h"
#include "Utils.h"

#include <vector>
#include <thread>


Simulation::Simulation(SimSpec s) : spec(s)
{
}

Simulation::~Simulation()
{
	if(nc)
		notcurses_stop(nc);
}

void Simulation::run()
{
	initNC();
	initSim();

	Clock dtClock, frameClock;
	running = true;

	while (running) {
		frameClock.tick();
		Timestep dt = dtClock.tick();

		handleEvents();
		update(dt);
		render(dt);

		// Cap the max amount of FPS
		int remaining = spec.targetFrameTime - frameClock.tick().milliseconds();
		if(remaining > 0)
			std::this_thread::sleep_for( std::chrono::milliseconds(remaining));
	}
}

void Simulation::handleEvents()
{
	unsigned int h = height, w = width;
	ncplane_dim_yx(plane, &height, &width);

	// If the dimensions changed we have to restart the simulation
	if(width != w || height != h)
	{
		initSim();
	}

	// User input listening
	ncinput input;
	if(notcurses_get_nblock(nc, &input))
	{
		if(input.id == 'q' || input.id == NCKEY_ESC)
		{
			running = 0;
		}
		else if(input.id == 'd' && input.evtype == NCTYPE_PRESS)
		{
			spec.showDebug = !spec.showDebug;
		}
	}
}

void Simulation::update(Timestep dt)
{
	for(auto &drop : drops)
	{
		drop.y += drop.speed * dt;

		if(drop.y >= height)
		{
			drop.x = rng.real(0, width-1);
			drop.y = 0.0f;
			drop.speed = rng.real(
					std::max(1,spec.speed - spec.speedRange),
					std::max(1,spec.speed + spec.speedRange)
					);
		}
	}
}

void Simulation::render(Timestep dt)
{
	ncplane_erase(plane);

	renderRain(dt);

	if(spec.showDebug)
		renderText(dt);

	notcurses_render(nc);
}

void Simulation::renderRain(Timestep dt)
{
	for(const auto &drop : drops)
	{
		int x = drop.x;
		int y = drop.y;

		if(x >= 0 && x < (int)width && y >= 0 && y < (int)height)
		{
			auto [r,g,b] = getDropColor(drop);
			ncplane_set_fg_rgb8(plane, r, g, b);
			ncplane_putchar_yx(plane, y, x, getDropChar(drop));
		}
	}
}

void Simulation::renderText(Timestep dt)
{
	ncplane_set_fg_rgb8(plane, 200,200,200);
	ncplane_printf_yx(plane, 0, 0, "FPS: %.1f", dt.fps());
	ncplane_printf_yx(plane, 1, 0, "Speed: %d", spec.speed);
	ncplane_printf_yx(plane, 2, 0, "Speed range: %d", spec.speedRange);
	ncplane_printf_yx(plane, 3, 0, "Density: %d", spec.rainDensity);
	ncplane_printf_yx(plane, 3, 0, "Charset: %s", spec.dropChars.c_str());
	ncplane_printf_yx(plane, 4, 0, "Drop count: %lu", drops.size());
}

void Simulation::initNC()
{
	notcurses_options options{};
	options.flags = NCOPTION_SUPPRESS_BANNERS;

	nc = notcurses_core_init(&options, stdout);

	if (!nc) {
		TEMPEST_ERR("notcurses_core_init");
	}

	plane = notcurses_stddim_yx(nc, &height, &width);
}

void Simulation::initSim()
{
	drops.clear();
	drops.reserve(getDropCount());
	for (int i = 0; i < getDropCount(); ++i)
	{
		drops.emplace_back(
				rng.real(0, width-1),
				rng.real(0, height),
				rng.real(std::max(1, spec.speed-spec.speedRange), std::max(1, spec.speed+spec.speedRange))
				);
	}
}

int Simulation::getDropCount()
{
	return spec.rainDensity * width * height / refScreenSurface;
}

char Simulation::getDropChar(const Raindrop &drop)
{
	int maxS = spec.speed + spec.speedRange;
	int tierSize = 2 * spec.speedRange / spec.dropChars.length() + 1;

	int curr = maxS - tierSize;
	for(char tier : spec.dropChars)
	{
		if(drop.speed >= curr) return tier;
		curr -= tierSize;
	}

	// This should never be reached
	return '?';
}

std::tuple<int,int,int> Simulation::getDropColor(const Raindrop &drop)
{
	int r = 230, g = 230, b = 255;
	float minTint = .6f, maxTint = 1;

	float lerp = std::max(0.0f, std::min(1.0f, (drop.speed - (float)(spec.speed - spec.speedRange))/2.0f/(float)std::max(1,spec.speedRange)));
	float moved = minTint + lerp * (maxTint - minTint);

	return {r*moved, g*moved, b*moved};
}
