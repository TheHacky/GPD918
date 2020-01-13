cbuffer MatrixBuffer
{
	float4x4 worldViewProjectionMatrix;
};

struct VertexOutput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

VertexOutput main(float4 pos : POSITION, float4 color : COLOR)
{
	VertexOutput output = (VertexOutput)0;

	pos.w = 1.0f;
	output.position = mul(pos, worldViewProjectionMatrix);

	output.color = color;

	return output;
}