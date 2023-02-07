#include "common.hlsl"

void main(in VS_IN In, out PS_IN Out)
{
	matrix wvp;
	wvp = mul(World, View);
	wvp = mul(wvp, Projection);
	
	float4 worldNormal, normal;
	normal = float4(In.Normal.xyz, 0.0);
	worldNormal = mul(normal, World);
	worldNormal = normalize(worldNormal);
	
    Out.Position = mul(In.Position, wvp);
    Out.WorldPosition = mul(In.Position, World);
    Out.Normal = worldNormal; //回転後の法線出力 In.Normalでなく回転後の法線を出力
    Out.TexCoord = In.TexCoord;
	Out.Diffuse = In.Diffuse;
}
