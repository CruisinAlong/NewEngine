struct PixelShaderInput
{
    float4 Color : COLOR;
    float4 Position : SV_Position;
    float4 LocalPosition : TEXCOORD0;
    nointerpolation uint FaceID : FACEID;

};

struct EntityID
{
    uint entityID;
};
struct SelectedEntity
{
    uint selectedEntityID;
};
struct SelectedFace
{
    uint selectedFaceID;
};
ConstantBuffer<EntityID> EntityIDCB : register(b2);
ConstantBuffer<SelectedEntity> SelectedEntityCB : register(b3);
ConstantBuffer<SelectedFace> SelectedFaceCB : register(b4);

struct PixelShaderOutput
{
    float4 Color : SV_Target0;
    int2 IDs : SV_Target1;
};

PixelShaderOutput main(PixelShaderInput IN)
{
    PixelShaderOutput OUT;
    float4 baseColor = IN.Color;
    bool SelectedFace = (EntityIDCB.entityID == SelectedEntityCB.selectedEntityID) && (IN.FaceID == SelectedFaceCB.selectedFaceID);
    if (SelectedFace)
        baseColor = float4(1.0, 0.85, 0.1, 1.0);
    OUT.Color = baseColor;
    OUT.IDs = int2(EntityIDCB.entityID, (int) IN.FaceID);
    return OUT;
}

/*float4 main(PixelShaderInput IN) : SV_TARGET
{
   
    return IN.Color;
}*/