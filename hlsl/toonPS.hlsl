#include "common.hlsl"

Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	//ピクセルの法線を正規化
	float4 normal = normalize(In.Normal);
	//光源計算をする
	float light = -dot(normal.xyz, Light.Direction.xyz);
    	// 明るさを決定
    if (light <= 0.1)
    {
        light = 0.3;
    }
    else if (light <= 0.5)
    {
        light = 0.7;
    }
    else
    {
        light = 1.0;
    }
    
    //カメラからピクセルへ向かうベクトル
    float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
    eyev = normalize(eyev); //正規化する
    
    float d = dot(normal.xyz, eyev);
    
    //テクスチャのピクセル色を取得
    outDiffuse =
		g_Texture.Sample(g_SamplerState, In.TexCoord);
    outDiffuse.rgb *=
		In.Diffuse.rgb * light; //明るさと色を乗算
    outDiffuse.a *=
		In.Diffuse.a; //α別計算
    
    if (d >= -0.3)
    {
        outDiffuse.rgb = 0;
    }
}


