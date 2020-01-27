cbuffer MatrixBuffer
{
	float4x4 worldMatrix;
	float4x4 worldViewProjectionMatrix;
	float4 tilingOffset;
};

struct VertexOutput
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOORD;
	float3 normal : NORMAL;
};

VertexOutput main(float4 pos : POSITION, float2 uv : TEXCOORD, float4 normal : NORMAL)
{
	VertexOutput output = (VertexOutput)0;

	pos.w = 1.0f;
	output.position = mul(pos, worldViewProjectionMatrix);

	normal.w = 0.0f;
	output.normal = normalize(mul(normal, worldMatrix).xyz);

	output.uv = uv * tilingOffset.xy + tilingOffset.zw;

	return output;
}