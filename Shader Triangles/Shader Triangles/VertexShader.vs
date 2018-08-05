#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

uniform float currentTime;

out vec3 fragColor;
out vec2 fragTexCoord;

void main() 
{
	if (color.xyz == 1.0)
	{
		vec3 updatingPosition = position * 0.6;
		updatingPosition.x = updatingPosition.x + (sin(currentTime) / 2);
		updatingPosition.y = updatingPosition.y + (cos(currentTime) / 2);
		gl_Position = vec4(updatingPosition, 1.0);
		fragColor = color; 
		
	}

	else
	{
		vec3 scaledPosition = position * 0.25;
		scaledPosition.x = scaledPosition.x - (sin(currentTime) / 2);
		scaledPosition.y = scaledPosition.y - (cos(currentTime) / 2);
		gl_Position = vec4(scaledPosition, 1.0);
		fragColor = color; 
	}

	fragTexCoord = texCoord;
}