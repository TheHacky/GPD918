Texture2D MainTexture;
SamplerState MainSampler;

cbuffer LightingBuffer
{
	float4 ambientLight;
	float3 lightVector;
	float lightIntensity;
	float4 lightColor;
};

struct PixelInput
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOORD;
	float3 normal : NORMAL;
};

float4 main(PixelInput input) : SV_TARGET
{
	float4 color = MainTexture.Sample(MainSampler, input.uv);
	float4 diffuse = 0;
	float4 specular = 0;
	float4 emission = 0;

	// diffuse light intensity
	float diffuseIntensity = dot(input.normal, -lightVector);
	if (diffuseIntensity > 0)
	{
		diffuse = lightColor * diffuseIntensity * lightIntensity;
	}

	// textureColor * (ambientLight + diffuseLight) + specularLight + emissionLight
	return color * (ambientLight + diffuse) + specular + emission;
}