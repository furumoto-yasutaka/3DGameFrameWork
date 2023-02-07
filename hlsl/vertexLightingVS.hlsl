#include "common.hlsl"

void main(in VS_IN In, out PS_IN Out)
{
	matrix wvp;
	wvp = mul(World, View);
	wvp = mul(wvp, Projection);
	
	float4 worldNormal, normal;
    normal = float4(In.Normal.xyz, 0.0f);
    worldNormal = mul(normal, World);
	worldNormal = normalize(worldNormal);

	float light = -dot(Light.Direction.xyz, worldNormal.xyz);
	light = saturate(light);

    Out.Position = mul(In.Position, wvp);
    Out.WorldPosition = mul(In.Position, World);
    Out.Normal = normal;
    Out.TexCoord = In.TexCoord;
	Out.Diffuse = In.Diffuse * Material.Diffuse * light * Light.Diffuse;
	Out.Diffuse += In.Diffuse * Material.Ambient * Light.Ambient;
	Out.Diffuse += Material.Emission;
	Out.Diffuse.a = In.Diffuse.a * Material.Diffuse.a;
}

