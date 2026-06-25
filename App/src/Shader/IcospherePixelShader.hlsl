struct VertexShaderOutput
{
    float4 Color : COLOR;
    float4 Position : SV_Position;
    float4 LocalPosition : TEXCOORD0;
};

float4 main(VertexShaderOutput IN) : SV_TARGET
{

    float4 topColor = float4(1.0f, 0.4f, 0.2f, 1.0f); // Vibrant Orange
    float4 bottomColor = float4(0.2f, 0.0f, 0.4f, 1.0f); // Deep Purple


    float gradientFactor = (IN.LocalPosition.y * 0.5f) + 0.5f;
    gradientFactor = saturate(gradientFactor);


    return lerp(bottomColor, topColor, gradientFactor);
}