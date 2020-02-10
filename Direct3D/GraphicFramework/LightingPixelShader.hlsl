Texture2D MainTexture;
Texture2D NormalMap;
SamplerState MainSampler;

cbuffer LightingBuffer
{
	float4 ambientLight;
	float3 lightVector;
	float lightIntensity;
	float4 lightColor;
	float3 lightPosition;
	float lightRange;
	float3 lightForward;
	float lightAngle;
	int type; // 0 = directional, 1 = point, ...
};

struct PixelInput
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOORD;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float3 binormal : BINORMAL;
	float3 cameraPos : TEXCOORD1;
	float3 posWorld : POSITION;
};

float4 calculateLight(float3 posWorld)
{
	float4 light = 0;

	if (type == 0)
	{
		// directional
		light.xyz = lightVector;
		light.w = lightIntensity;
	}
	else if (type == 1)
	{
		// point
		float3 lightVec = posWorld - lightPosition;
		float l = length(lightVec);
		if (l <= lightRange)
		{
			float abbreviation = 1.0f / (1.0f + 0.5f * l + 0.1f * l * l);
			light.xyz = lightVec / l;
			light.w = lightIntensity * abbreviation;
		}
	}
	else if (type == 2)
	{
		// spot
		float3 lightVec = posWorld - lightPosition;
		float l = length(lightVec);
		if (l <= lightRange)
		{
			lightVec = lightVec / l;
			float d = dot(lightVec, lightForward);
			if (d >= lightAngle)
			{
				float abbreviation = 1.0f / (1.0f + 0.5f * l + 0.1f * l * l);
				light.xyz = lightVec;
				light.w = lightIntensity * abbreviation;
			}
		}
	}

	return light;
}

float3 calculateNormal(PixelInput input)
{
	float3 normal;

	float3 normalMapColor = NormalMap.Sample(MainSampler, input.uv).rgb * 2.0f - 1.0f; // convert range [0;1] to [-1;1]
	normal = input.tangent * normalMapColor.r;
	normal += input.binormal * normalMapColor.g;
	normal += input.normal * normalMapColor.b;

	return normal;
}

float4 main(PixelInput input) : SV_TARGET
{
	float4 color = MainTexture.Sample(MainSampler, input.uv);
	float4 diffuse = 0;
	float4 specular = 0;
	float4 emission = 0;
	//float4 emission = lightColor * color.a;

	// calculate light vector
	float4 light = calculateLight(input.posWorld);
	if (light.w > 0.0f)
	{
		// diffuse light intensity (Lambert)
		float3 normal = normalize(calculateNormal(input));
		float diffuseIntensity = dot(normal, -light.xyz);
		if (diffuseIntensity > 0)
		{
			diffuse = saturate(lightColor * diffuseIntensity * light.w);

			float3 viewVector = normalize(input.cameraPos - input.posWorld);

			//// specular light intensity (Phong)
			//float3 reflectionVector = normalize(2 * normal * diffuseIntensity - light.xyz);
			////float3 reflectionVector = reflect(light.xyz, normal);
			//float specularIntensity = dot(reflectionVector, viewVector);
			//
			//if (specularIntensity > 0)
			//{
			//	float phongExponent = 128;
			//	specular = saturate(lightColor * pow(specularIntensity, phongExponent) * light.w);
			//}

			// specular light intensity (Blinn-Phong)
			float3 halfVector = (viewVector - light.xyz) * 0.5f;
			float specularIntensity = dot(normal, halfVector);

			if (specularIntensity > 0)
			{
				float phongExponent = 256;
				specular = saturate(lightColor * pow(specularIntensity, phongExponent) * light.w * color.a);
			}
		}
	}
		
	// textureColor * (ambientLight + diffuseLight) + specularLight + emissionLight
	return saturate(saturate(saturate(color * saturate(ambientLight + diffuse)) + specular) + emission);
}
