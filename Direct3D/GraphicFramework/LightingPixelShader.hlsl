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
	float2 uv : TEXCOORD0;
	float3 normal : NORMAL;
	float3 cameraPos : TEXCOORD1;
	float3 posWorld : POSITION;
};

float4 main(PixelInput input) : SV_TARGET
{
	float4 color = MainTexture.Sample(MainSampler, input.uv);
	float4 diffuse = 0;
	float4 specular = 0;
	float4 emission = 0;

	// diffuse light intensity (Lambert)
	float3 normal = normalize(input.normal);
	float diffuseIntensity = dot(normal, -lightVector);
	if (diffuseIntensity > 0)
	{
		diffuse = saturate(lightColor * diffuseIntensity * lightIntensity);

		float3 viewVector = normalize(input.cameraPos - input.posWorld);
		
		//// specular light intensity (Phong)
		//float3 reflectionVector = normalize(2 * normal * diffuseIntensity - lightVector);
		////float3 reflectionVector = reflect(lightVector, normal);
		//float specularIntensity = dot(reflectionVector, viewVector);
		//
		//if (specularIntensity > 0)
		//{
		//	float phongExponent = 128;
		//	specular = saturate(lightColor * pow(specularIntensity, phongExponent) * lightIntensity);
		//}

		// specular light intensity (Blinn-Phong)
		float3 halfVector = (viewVector - lightVector) * 0.5f;
		float specularIntensity = dot(normal, halfVector);

		if (specularIntensity > 0)
		{
			float phongExponent = 256;
			specular = saturate(lightColor * pow(specularIntensity, phongExponent) * lightIntensity * color.a);
		}
	}
	
	// textureColor * (ambientLight + diffuseLight) + specularLight + emissionLight
	return saturate(saturate(saturate(color * saturate(ambientLight + diffuse)) + specular) + emission);
}