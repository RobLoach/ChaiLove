#include "event.h"

#include "../ChaiLove.h"
#include <SDL.h>

namespace love {

void event::quit() {
	m_shouldclose = true;
}

void event::update() {
	if (ChaiLove::hasInstance()) {
		// Poll all the inputs.
		ChaiLove::input_poll_cb();

		// Poll all SDL events.
		while (SDL_PollEvent(&sdlEvent)) {
			switch (sdlEvent.type) {
				case SDL_QUIT:
					quit();
					break;
			}
		}
	}
}

}  // namespace love
