set(GRAPHICS_Headers
	mainrenderer.h
	include.h
)

set(GRAPHICS_Sources
	${GRAPHICS_Headers}
	mainrenderer.cpp
)

add_library(graphics ${GRAPHICS_Sources})
