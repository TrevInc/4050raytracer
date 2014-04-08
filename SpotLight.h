#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include "DirectionalLight.h"

#define PI 3.14159265

class SpotLight : public DirectionalLight {
	private:
		double lightShade;
		double fallOffIntensity;
	public:
		SpotLight(
			String name, 
			const enum Colors color,
			const Vector location, 
			const Vector direction, 
			const double intensity,
			const double lightShade,
			const double fallOffIntensity);
		SpotLight(
			String name, 
			const Color color, 
			const Vector location,
			const Vector direction, 
			const double intensity,
			const double lightShade,
			const double fallOffIntensity);
		const double getLightShade() const;
		const double getFallOffIntensity() const;
		void setLightShade(const double lightShade);
		void setFallOffIntensity(const double fallOffIntensity);
		virtual const double getIntensity(const Vector *hitPoint) const;
};

#endif
