#ifndef CONFIG_H
#define CONFIG_H

namespace config {
    #include <string>
    const std::string MGE_MODEL_PATH ("mge/models/");
    const std::string MGE_TEXTURE_PATH ("mge/textures/");
	const std::string MGE_SPECULAR_PATH ("mge/specular/");
	const std::string MGE_SOUND_PATH("mge/sounds/");
    const std::string MGE_SHADER_PATH ("mge/shaders/");
    const std::string MGE_FONT_PATH ("mge/fonts/");
	const std::string MGE_SCENE_PATH("mge/scenes/");
	const std::string MGE_LUA_PATH("mge/lua scripts/");

	const float TOTAL_MOVE_TIME = 0.8f;
}


#endif
