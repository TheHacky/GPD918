Texture2D MainTexture;
SamplerState MainSampler;

struct PixelInput
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOORD;
};

float4 main(PixelInput input) : SV_TARGET
{
	float4 color = MainTexture.Sample(MainSampler, input.uv);
	return color;
}