#version 430 core 
 

in layout(location = 0) vec3 vposition;
in layout(location = 1) vec2 vtexcoord;
in layout(location = 2) vec3 vnormal;
 
out vec2 texcoord;
out vec3 color;
 
 struct Light
 {
 vec3 ambient;
 vec3 diffuse;
 vec3 specular;
 vec4 position;
 };

uniform Light light;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

 
void main()
{
	texcoord = vtexcoord;
	vec3 ambient = light.ambient;
	// diffuse
	mat4 model_view = view*model;
	vec4 position = model_view*vec4(vposition,1);
	vec3 light_dir = normalize(vec3(light.position - position));
	float intensity = max(dot(light_dir, vnormal),0);
	vec3 diffuse = light.diffuse + intensity;
	//specular
	vec3 specular = vec3(0);
	if (intensity > 0)
	{
		vec3 reflection = reflect(-light_dir, vnormal);
		vec3 view_dir = normalize(-vec3(position));
		intensity = max(dot(reflection, view_dir), 0);
		intensity = pow(intensity, 32.0);
		specular = color * intensity;
	}

	color=ambient+diffuse;

	mat4 mvp = projection * view * model;
	gl_Position = mvp * vec4(vposition, 1.0);
}