#version 330 core

out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

uniform vec3 lightPos;
uniform vec3 viewPos;

uniform sampler2D texture1;

void main()
{
    vec3 color = texture(texture1,TexCoord).rgb;
    float ambientStrength = 0.05;
    vec3 ambient = ambientStrength * color;
    
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm,lightDir),0.0);
    vec3 diffuse = diff * color;

    vec3 viewDir = normalize( viewPos-FragPos);
    float spec = 0.0;
    vec3 halfwayDir = normalize(viewDir+lightDir);
    spec = pow(max(dot(norm,halfwayDir),0.0),32.0);
    vec3 specular = vec3(0.3) * spec;
    vec4 result = vec4((ambient + diffuse + specular),1.0) * texture(texture1,TexCoord);
    FragColor = result;
}