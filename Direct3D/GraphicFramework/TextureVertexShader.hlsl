cbuffer MatrixBuffer
{
	float4x4 worldViewProjectionMatrix;
	float4 tilingOffset;
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

	output.uv = uv * tilingOffset.xy + tilingOffset.zw;

	return output;
}