#include "SpotLight.h"

SpotLight::SpotLight(
	String name,
	const Color color,
	const Vector location,
	const Vector direction,
	const double intensity,
	const double lightShade,
	const double fallOffIntensity) : 
		DirectionalLight(name, color, location, direction, intensity), 
		lightShade(cos(lightShade * PI / 180)), 
		fallOffIntensity(fallOffIntensity) {}

inline const double SpotLight::getIntensity(const Vector *hitPoint) const {
		double light = (*hitPoint - location).normalize() * direction;
		if (light < lightShade) return 0;
		return pow(light, fallOffIntensity) * intensity;
}

inline const double SpotLight::getLightShade() const {return lightShade;}

inline const double SpotLight::getFallOffIntensity() const {return fallOffIntensity;}

void SpotLight::setLightShade(const double lightShade) {this->lightShade = lightShade;}

void SpotLight::setFallOffIntensity(const double fallOffIntensity) {this->fallOffIntensity = fallOffIntensity;}

