cbuffer MatrixBuffer
{
	float4x4 worldMatrix;
	float4x4 worldViewProjectionMatrix;
	float4 tilingOffset;
	float3 cameraWorldPosition;
};

struct VertexInput
{
	float4 pos : POSITION;
	float2 uv : TEXCOORD;
	float4 normal : NORMAL;
	float4 tangent : TANGENT;
	float4 binormal : BINORMAL;
};

struct VertexOutput
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOORD;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float3 binormal : BINORMAL;
	float3 cameraPos : TEXCOORD1;
	float3 posWorld : POSITION;
};

VertexOutput main(VertexInput input)
{
	VertexOutput output = (VertexOutput)0;

	input.pos.w = 1.0f;
	output.position = mul(input.pos, worldViewProjectionMatrix);
	output.posWorld = mul(input.pos, worldMatrix).xyz;

	input.normal.w = 0.0f;
	output.normal = normalize(mul(input.normal, worldMatrix).xyz);

	input.tangent.w = 0.0f;
	output.tangent = normalize(mul(input.tangent, worldMatrix).xyz);

	input.binormal.w = 0.0f;
	output.binormal = normalize(mul(input.binormal, worldMatrix).xyz);

	output.uv = input.uv * tilingOffset.xy + tilingOffset.zw;

	output.cameraPos = cameraWorldPosition;

	return output;
}