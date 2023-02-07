/*******************************************************************************
*
*	タイトル：	テクスチャ管理用静的クラス	[ textureContainer.cpp ]
*	※ モデルに付属しているテクスチャは管理に含みません
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "textureContainer.h"
#include "manager.h"
#include "scene.h"

void TextureContainer::Init()
{
	// 固定アセット
	AddTexture("Black", "Default\\black.png",
		1, 1, (int)Scene::SceneTag::Everything);

	AddTexture("White", "Default\\white.png",
		1, 1, (int)Scene::SceneTag::Everything);


	// Logoシーン
	AddTexture("DevelopLogo", "Logo\\Logo.png",
		1, 1, (int)Scene::SceneTag::Everything);

	// GameUi
	AddTexture("PlayerHp_Frame", "Game\\hartSub.png",
		1, 1, (int)Scene::SceneTag::Everything);
	AddTexture("PlayerHp_Inside", "Game\\hart.png",
		1, 1, (int)Scene::SceneTag::Everything);
}

void TextureContainer::Uninit()
{
	// すべてのテクスチャを解放
	for (auto itr : m_TextureInfo)
	{
		itr.second->Unload();
		delete itr.second;
	}
}

/*******************************************************************************
*	すべてのテクスチャに対して使用フラグに応じて
*	ロード・アンロードを実行(シーン変更時用)
*******************************************************************************/
void TextureContainer::LoadAndUnload_AllTexture()
{
	for (auto itr = m_TextureInfo.begin(); itr != m_TextureInfo.end(); itr++)
	{
		if (itr->second->GetTag() & Manager::GetScene()->GetTag())
		{// 次のシーンで使う場合
			itr->second->Load();
		}
		else
		{// 次のシーンで使わない場合
			itr->second->Unload();
		}
	}
}

/*******************************************************************************
*	テクスチャ取得(名称で検索)
*******************************************************************************/
Texture* TextureContainer::GetTexture_InName(string Name)
{
	decltype(m_TextureInfo)::iterator itr = m_TextureInfo.find(Name);
	if (itr != m_TextureInfo.end())
	{
		return itr->second;
	}
	else
	{
		string str = string("存在しない名称のテクスチャの取得が要求されました。\n") + Name;
		MessageBox(GetWindow(),
			TEXT(str.c_str()),
			TEXT("textureContainer:Error"),
			MB_OK | MB_ICONERROR);
		return NULL;
	}
}

/*******************************************************************************
*	テクスチャ追加
*******************************************************************************/
void TextureContainer::AddTexture(string Name, string Path, int WidthDiv, int HeightDiv, int Tag)
{
	string fullPath = "asset\\texture\\" + Path;

	// 要素がマップに存在するか確認
	if (m_TextureInfo.count(string(Name)))
	{
		string str = string("すでに存在する名称でテクスチャの追加が要求されました。\n") + fullPath + "\nこのテクスチャは読み込まれません。";
		MessageBox(GetWindow(),
			TEXT(str.c_str()),
			TEXT("textureContainer:Error"),
			MB_OK | MB_ICONERROR);
		return;
	}
	else
	{
		m_TextureInfo[Name] = DBG_NEW Texture(fullPath.c_str());
		m_TextureInfo[Name]->SetWidthDiv(WidthDiv);
		m_TextureInfo[Name]->SetHeightDiv(HeightDiv);
		m_TextureInfo[Name]->AddTag(Tag);
	}
}
