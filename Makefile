CC = g++
C = cpp
H = h

PROJECT = raytrace

CFLAGS = -g -O4 -Wall `Magick++-config --cppflags`
LFLAGS = -g -O4 -Wall `Magick++-config --ldflags`

ifeq ("$(shell uname)", "Darwin")
  LDFLAGS = -framework Foundation -framework GLUT -framework OpenGL -lm
else
  ifeq ("$(shell uname)", "Linux")
    LDFLAGS = -lglut -lGL -lGLU -lMagick++ -lm
  endif
endif

HFILES = rayTracer.${H}\
			Object.${H}\
			ColoredObject.${H}\
			RGBApixel.${H}\
			Pixmap.${H}\
			Image.${H}\
			Node.${H}\
			List.${H}\
			Scene.${H}\
			Shape.${H}\
			Sphere.${H}\
			Vector.${H}\
			Color.${H}\
			EnumColors.${H}\
			Light.${H}\
			PointLight.${H}\
			ParallelLight.${H}\
			SpotLight.${H}\
			Plane.${H}\
			Camera.${H}\
			EnumMaterials.${H}\
			HitData.${H}\
			Material.${H}\
			Parser.${H}\
			Tokenizer.${H}\
			RayTracer.${H}\
			DirectionalLight.${H}\
			Triangle.${H}\
			String.${H}\
			BoundingBox.${H}

SFILES = main.${C}\
			Object.${C}\
			ColoredObject.${C}\
			Pixmap.${C}\
			Image.${C}\
			Node.${C}\
			List.${C}\
			Scene.${C}\
			Shape.${C}\
			Sphere.${C}\
			Vector.${C}\
			Color.${C}\
			Light.${C}\
			PointLight.${C}\
			ParallelLight.${C}\
			SpotLight.${C}\
			Plane.${C}\
			Camera.${C}\
			Material.${C}\
			Parser.${C}\
			Tokenizer.${C}\
			RayTracer.${C}\
			DirectionalLight.${C}\
			Triangle.${C}\
			String.${C}\
			BoundingBox.${C}

OFILES = Object.o\
			ColoredObject.o\
			Pixmap.o\
			Image.o\
			Node.o\
			List.o\
			Scene.o\
			Shape.o\
			Sphere.o\
			Vector.o\
			Color.o\
			Light.o\
			PointLight.o\
			ParallelLight.o\
			SpotLight.o\
			Plane.o\
			Camera.o\
			Material.o\
			Parser.o\
			Tokenizer.o\
			RayTracer.o\
			DirectionalLight.o\
			Triangle.o\
			String.o\
			BoundingBox.o

${PROJECT}: main.o $(OFILES)
	${CC} $(CFLAGS) -o ${PROJECT} main.o $(OFILES) $(LDFLAGS)

main.o: main.${C} $(HFILES)
	${CC} $(CFLAGS) -c main.${C}

Object.o: Object.${C} Object.${H}
	${CC} $(CFLAGS) -c Object.${C}

ColoredObject.o: ColoredObject.${C} ColoredObject.${H}
	${CC} $(CFLAGS) -c ColoredObject.${C}

Pixmap.o: Pixmap.${C} Pixmap.${H}
	${CC} $(CFLAGS) -c Pixmap.${C}

Image.o: Image.${C} Image.${H}
	${CC} $(CFLAGS) -c Image.${C}

Node.o: Node.${C} Node.${H}
	${CC} $(CFLAGS) -c Node.${C}
	
List.o: List.${C} List.${H}
	${CC} $(CFLAGS) -c List.${C}
	
Scene.o: Scene.${C} Scene.${H}
	${CC} $(CFLAGS) -c Scene.${C}
	
Shape.o: Shape.${C} Shape.${H}
	${CC} $(CFLAGS) -c Shape.${C}

Sphere.o: Sphere.${C} Sphere.${H}
	${CC} $(CFLAGS) -c Sphere.${C}

Vector.o: Vector.${C} Vector.${H}
	${CC} $(CFLAGS) -c Vector.${C}
	
Color.o: Color.${C} Color.${H}
	${CC} $(CFLAGS) -c Color.${C}

Light.o: Light.${C} Light.${H}
	${CC} $(CFLAGS) -c Light.${C}

PointLight.o: PointLight.${C} PointLight.${H}
	${CC} $(CFLAGS) -c PointLight.${C}

ParallelLight.o: ParallelLight.${C} ParallelLight.${H}
	${CC} $(CFLAGS) -c ParallelLight.${C}

SpotLight.o: SpotLight.${C} SpotLight.${H}
	${CC} $(CFLAGS) -c SpotLight.${C}

Plane.o: Plane.${C} Plane.${H}
	${CC} $(CFLAGS) -c Plane.${C}

Camera.o: Camera.${C} Camera.${H}
	${CC} $(CFLAGS) -c Camera.${C}
	
Material.o: Material.${C} Material.${H}
	${CC} $(CFLAGS) -c Material.${C}
	
Parser.o: Parser.${C} Parser.${H}
	${CC} $(CFLAGS) -c Parser.${C}
	
Tokenizer.o: Tokenizer.${C} Tokenizer.${H}
	${CC} $(CFLAGS) -c Tokenizer.${C}

RayTracer.o: RayTracer.${C} RayTracer.${H}
	${CC} $(CFLAGS) -c RayTracer.${C}

DirectionalLight.o: DirectionalLight.${C} DirectionalLight.${H}
	${CC} $(CFLAGS) -c DirectionalLight.${C}
	
Triangle.o: Triangle.${C} Triangle.${H}
	${CC} $(CFLAGS) -c Triangle.${C}

String.o: String.${C} String.${H}
	${CC} $(CFLAGS) -c String.${C}
	
BoundingBox.o: BoundingBox.${C} BoundingBox.${H}
	${CC} $(CFLAGS) -c BoundingBox.${C}

clean:
	rm -f core.* *.o *~ core.* *.tar *.gch

tar:
	tar -cf ${PROJECT}.tar ${SFILES} ${HFILES} *.txt run.sh Makefile
