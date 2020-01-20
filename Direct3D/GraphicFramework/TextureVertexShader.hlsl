cbuffer MatrixBuffer
{
	float4x4 worldViewProjectionMatrix;
};

struct VertexOutput
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOORD;
};

VertexOutput main(float4 pos : POSITION, float2 uv : TEXCOORD)
{
	VertexOutput output = (VertexOutput)0;

	pos.w = 1.0f;
	output.position = mul(pos, worldViewProjectionMatrix);

	output.uv = uv;

	return output;
}