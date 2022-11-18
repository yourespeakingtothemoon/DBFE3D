#version 430 core 

in layout(location = 0) vec3 vposition;
in layout(location = 1) vec2 vtexcoord;

out vec3 color;

uniform struct Material
{
	vec3 color;
} material;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	color = material.color;

	mat4 mvp = projection * view * model;
	gl_Position = mvp * vec4(vposition, 1.0);
}
