cbuffer MatrixBuffer
{
	float4x4 worldMatrix;
	float4x4 worldViewProjectionMatrix;
	float4 tilingOffset;
	float3 cameraWorldPosition;
};

struct VertexOutput
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOORD;
	float3 normal : NORMAL;
	float3 cameraPos : TEXCOORD1;
	float3 posWorld : POSITION;
};

VertexOutput main(float4 pos : POSITION, float2 uv : TEXCOORD, float4 normal : NORMAL)
{
	VertexOutput output = (VertexOutput)0;

	pos.w = 1.0f;
	output.position = mul(pos, worldViewProjectionMatrix);
	output.posWorld = mul(pos, worldMatrix).xyz;

	normal.w = 0.0f;
	output.normal = normalize(mul(normal, worldMatrix).xyz);

	output.uv = uv * tilingOffset.xy + tilingOffset.zw;

	output.cameraPos = cameraWorldPosition;

	return output;
}