#region Vertex

#version 440 core
			
layout(location = 0) in vec4 a_vertexPosition;
layout(location = 1) in vec4 a_tint;

out vec4 tint;

layout (std140) uniform b_camera
{
	mat4 u_view;
	mat4 u_projection;
};

void main()
{
	tint = a_tint;
	gl_Position =  u_projection * u_view * a_vertexPosition;
}
				
#region Fragment

#version 440 core
			
layout(location = 0) out vec4 colour;

in vec4 tint;

void main()
{
	colour = tint;
}