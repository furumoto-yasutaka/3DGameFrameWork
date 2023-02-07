/*******************************************************************************
*
*	タイトル：	ゲームオブジェクトクラス	[ gameObject.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "gameObject.h"
#include "component.h"
#include "manager.h"
#include "debugManager.h"

void GameObject::Init(string Name, int Layer, int Tag,
	unordered_multimap<string, GameObject*>::iterator MapItr,
	list<GameObject*>::iterator OrderedListItr)
{
	// 初期化
	m_Name = Name;
	m_Layer = Layer;
	m_Tag = Tag;
	m_MapIterator = MapItr;
	m_OrderedListIterator = OrderedListItr;
	m_LocalPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_LocalRotation = Math::GetQuaternionIdentity();
	m_LocalScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

#ifdef _DEBUG
	InitDebug();
#endif
}

void GameObject::LateInit()
{
	for (int i = 0; i < (int)Component::ProcGroup::Length; i++)
	{
		for (Component* c : m_ComponentList[i])
		{
			c->LateInit();
		}
	}
}

void GameObject::Uninit()
{
	// コンポーネントを全て解放
	for (int i = 0; i < (int)Component::ProcGroup::Length; i++)
	{
		for (Component* c : m_ComponentList[i])
		{
			c->Uninit();
			delete c;
		}
		m_ComponentList[i].clear();
	}

	// 自身に関する親子関係を全て削除
	SetParent(NULL);

	list<GameObject*> tempChild = m_Child;
	for (GameObject* obj : tempChild)
	{
		obj->SetParent(NULL);
	}

#ifdef _DEBUG
	UninitDebug();
#endif
}

void GameObject::Update(int Group)
{
	// 非アクティブの場合は何もせず終了
	if (!m_IsActive) { return; }

	for (Component* c : m_ComponentList[Group])
	{
		// コンポーネントが非アクティブの場合はスキップする
		if (!c->GetActive()) { continue; }

		c->Update();
	}
}

void GameObject::LateUpdate(int Group)
{
	// 非アクティブの場合は何もせず終了
	if (!m_IsActive) { return; }

	for (Component* c : m_ComponentList[Group])
	{
		// コンポーネントが非アクティブの場合はスキップする
		if (!c->GetActive()) { continue; }

		c->LateUpdate();
	}
}

void GameObject::Draw(int Group)
{
	// 非アクティブの場合は何もせず終了
	if (!m_IsActive) { return; }

	for (Component* c : m_ComponentList[Group])
	{
		// コンポーネントが非アクティブの場合はスキップする
		if (!c->GetActive()) { continue; }

		c->Draw();
	}
}

/*******************************************************************************
*	コンポーネントの削除確認
*******************************************************************************/
void GameObject::CheckComponentDestroy()
{
	// 削除予約のあったコンポーネントを削除する
	for (int i = 0; i < (int)Component::ProcGroup::Length; i++)
	{
		m_ComponentList[i].remove_if([](Component* component)
			{ return component->Destroy(); }
		);
	}
}

/*******************************************************************************
*	親オブジェクト設定
*******************************************************************************/
void GameObject::SetParent(GameObject* Parent, int RemoveOption, int SetOption)
{
	// 前の親オブジェクトから自身の情報を削除
	if (m_Parent)
	{
		CheckRemoveOption(RemoveOption, m_Parent);

		m_Parent->RemoveChild(this);
	}

	// 新しい親オブジェクトに自身の情報を登録
	if (Parent)
	{
		CheckSetOption(SetOption, Parent);
		Parent->AddChild(this);
	}

	// 親を変更
	m_Parent = Parent;
}

/*******************************************************************************
*	マトリクスを取得
*******************************************************************************/
D3DXMATRIX GameObject::GetMatrix()
{
	D3DXMATRIX scale, rot, trans;
	D3DXMatrixScaling(&scale, m_LocalScale.x, m_LocalScale.y, m_LocalScale.z);
	D3DXMatrixRotationQuaternion(&rot, &m_LocalRotation);
	D3DXMatrixTranslation(&trans, m_LocalPosition.x, m_LocalPosition.y, m_LocalPosition.z);
	return scale * rot * trans;
}

/*******************************************************************************
*	正面方向の単位ベクトルを取得
*******************************************************************************/
D3DXVECTOR3 GameObject::GetForward()
{
	D3DXMATRIX rot;
	D3DXQUATERNION q = GetWorldRotation();
	D3DXMatrixRotationQuaternion(&rot, &q);

	D3DXVECTOR3 forward = { rot._31, rot._32, rot._33 };

	return forward;
}

/*******************************************************************************
*	上方向の単位ベクトルを取得
*******************************************************************************/
D3DXVECTOR3 GameObject::GetUp()
{
	D3DXMATRIX rot;
	D3DXQUATERNION q = GetWorldRotation();
	D3DXMatrixRotationQuaternion(&rot, &q);

	D3DXVECTOR3 up = { rot._21, rot._22, rot._23 };

	return up;
}

/*******************************************************************************
*	右方向の単位ベクトルを取得
*******************************************************************************/
D3DXVECTOR3 GameObject::GetRight()
{
	D3DXMATRIX rot;
	D3DXQUATERNION q = GetWorldRotation();
	D3DXMatrixRotationQuaternion(&rot, &q);

	D3DXVECTOR3 right = { rot._11, rot._12, rot._13 };

	return right;
}

/*******************************************************************************
*	自身とその子オブジェクトの削除を予約
*******************************************************************************/
void GameObject::SetDestroy()
{
	// 自身の削除を予約
	m_IsDestroy = true;

	// 子オブジェクトの削除を予約
	for (GameObject* obj : m_Child)
	{
		obj->SetDestroy();
	}
}

/*******************************************************************************
*	削除処理
*******************************************************************************/
bool GameObject::Destroy()
{
	if (m_IsDestroy)
	{
		Uninit();
		delete this;
		return true;
	}
	else
	{
		return false;
	}
}

/*******************************************************************************
*	自身のローカルマトリクスの原点におけるワールドマトリクス
*	(親のワールドマトリクス)取得
*******************************************************************************/
D3DXMATRIX GameObject::GetLocalMatrixOrigin()
{
	// 親が存在する場合再帰的にマトリックスを求める
	if (m_Parent)
	{
		return m_Parent->GetWorldMatrix();
	}
	else
	{
		return Math::GetMatrixIdentity();
	}
}

/*******************************************************************************
*	ワールドマトリクス取得
*******************************************************************************/
D3DXMATRIX GameObject::GetWorldMatrix(D3DXMATRIX Matrix)
{
	// 親が存在する場合再帰的にマトリックスを求める
	if (m_Parent)
	{
		return m_Parent->GetWorldMatrix(Matrix * GetMatrix());
	}
	else
	{
		return Matrix * GetMatrix();
	}
}

/*******************************************************************************
*	自身のローカル座標の原点におけるワールド座標
*	(親のワールド座標)取得
*******************************************************************************/
D3DXVECTOR3 GameObject::GetLocalPositionOrigin()
{
	// 親が存在する場合再帰的に座標を求める
	if (m_Parent)
	{
		return m_Parent->GetWorldPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	else
	{
		return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

/*******************************************************************************
*	ワールド座標取得
*******************************************************************************/
D3DXVECTOR3 GameObject::GetWorldPosition(D3DXVECTOR3 Position)
{
	// 親が存在する場合再帰的に座標を求める
	if (m_Parent)
	{
		return m_Parent->GetWorldPosition(Position + m_LocalPosition);
	}
	else
	{
		return Position + m_LocalPosition;
	}
}

/*******************************************************************************
*	ワールド座標設定
*******************************************************************************/
void GameObject::SetWorldPosition(D3DXVECTOR3 Position)
{
	// 親のワールド座標から引いて求める
	if (m_Parent)
	{
		m_LocalPosition = Position - m_Parent->GetWorldPosition();
	}
	else
	{
		m_LocalPosition = Position;
	}
}

/*******************************************************************************
*	自身のローカルローテーションの原点におけるワールドローテーション
*	(親のワールドローテーション)取得
*******************************************************************************/
D3DXQUATERNION GameObject::GetLocalRotationOrigin()
{
	// 親が存在する場合再帰的に回転を求める
	if (m_Parent)
	{
		return m_Parent->GetWorldRotation(Math::GetQuaternionIdentity());
	}
	else
	{
		return Math::GetQuaternionIdentity();
	}
}

/*******************************************************************************
*	ワールドローテーション取得
*******************************************************************************/
D3DXQUATERNION GameObject::GetWorldRotation(D3DXQUATERNION Rotation)
{
	// 親が存在する場合再帰的に回転を求める
	if (m_Parent)
	{
		return m_Parent->GetWorldRotation(Rotation * m_LocalRotation);
	}
	else
	{
		return Rotation * m_LocalRotation;
	}
}

/*******************************************************************************
*	ワールドローテーション設定
*******************************************************************************/
void GameObject::SetWorldRotation(D3DXQUATERNION Rotation)
{
	D3DXVECTOR3 euler = Math::QuaternionToEulerAngle(Rotation);
	D3DXVECTOR3 eulerParent = Math::QuaternionToEulerAngle(m_Parent->GetWorldRotation());

	// 親のワールドスケールから引いて求める
	if (m_Parent)
	{
		m_LocalRotation = Math::EulerAngleToQuaternion(euler - eulerParent);
	}
	else
	{
		m_LocalRotation = Rotation;
	}
}

/*******************************************************************************
*	自身のローカルスケールの原点におけるワールドスケール
*	(親のワールドスケール)取得
*******************************************************************************/
D3DXVECTOR3 GameObject::GetLocalScaleOrigin()
{
	// 親が存在する場合再帰的に拡縮を求める
	if (m_Parent)
	{
		return m_Parent->GetWorldScale(D3DXVECTOR3());
	}
	else
	{
		return D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	}
}

/*******************************************************************************
*	ワールドスケール取得
*******************************************************************************/
D3DXVECTOR3 GameObject::GetWorldScale(D3DXVECTOR3 Scale)
{
	D3DXVECTOR3 s = { Scale.x * m_LocalScale.x, Scale.y * m_LocalScale.y, Scale.z * m_LocalScale.z };

	// 親が存在する場合再帰的に拡縮を求める
	if (m_Parent)
	{
		return m_Parent->GetWorldScale(s);
	}
	else
	{
		return s;
	}
}

/*******************************************************************************
*	ワールドスケール設定
*******************************************************************************/
void GameObject::SetWorldScale(D3DXVECTOR3 Scale)
{
	// 親のワールドスケールから引いて求める
	if (m_Parent)
	{
		m_LocalScale = Scale - m_Parent->GetWorldScale();
	}
	else
	{
		m_LocalScale = Scale;
	}
}

/*******************************************************************************
*	オブジェクトリストのイテレータを上書き
*******************************************************************************/
void GameObject::SetIterator(unordered_multimap<string, GameObject*>::iterator MapItr,
	list<GameObject*>::iterator OrderedListItr)
{
	m_MapIterator = MapItr;
	m_OrderedListIterator = OrderedListItr;
}

/*******************************************************************************
*	全てのコンポーネントを取得する
*******************************************************************************/
list<Component*> GameObject::GetComponentAll()
{
	list<Component*> result;
	for (int i = 0; i < (int)Component::ProcGroup::Length; i++)
	{
		for (Component* c : m_ComponentList[i])
		{
			result.push_back(c);
		}
	}

	return result;
}

/*******************************************************************************
*	一番親のオブジェクトを取得
*******************************************************************************/
GameObject* GameObject::GetRoot()
{
	if (m_Parent)
	{
		return m_Parent->GetRoot();
	}
	else
	{
		return this;
	}
}

/*******************************************************************************
*	子オブジェクトを添え字を指定して取得
*******************************************************************************/
GameObject* GameObject::GetChild(int index)
{
	if (m_Child.size() < (unsigned int)index + 1)
	{
		return NULL;
	}

	auto itr = m_Child.begin();
	for (int i = 0; i < index; i++)
	{
		itr++;
	}

	return (*itr);
}

/*******************************************************************************
*	自身がアクティブであるかを取得
*******************************************************************************/
bool GameObject::GetActive()
{
	if (m_Parent)
	{
		return m_Parent->GetActive();
	}
	else
	{
		return m_IsActive;
	}
}

/*******************************************************************************
*	オブジェクトの静的設定を変更する
*******************************************************************************/
void GameObject::SetStatic(bool Value)
{
	if (m_IsStatic == Value) { return; }

	if (Value)
	{
		Manager::GetScene()->SetStatic(this);
	}
	else
	{
		Manager::GetScene()->SetDynamic(this);
	}
	
	m_IsStatic = Value;
}

/*******************************************************************************
*	オブジェクトの名前を変更
*******************************************************************************/
void GameObject::SetName(string NewName)
{
	Manager::GetScene()->SetObjectName(this, NewName);
	m_Name = NewName;
}

void GameObject::CheckRemoveOption(int Option, GameObject* Parent)
{
	if (Option & (int)SetParentOption::KeepPos)
	{
		m_LocalPosition += Parent->GetWorldPosition();
	}
	if (Option & (int)SetParentOption::KeepScale)
	{
		D3DXVECTOR3 s = Parent->GetWorldScale();
		m_LocalScale = {
			m_LocalScale.x * s.x,
			m_LocalScale.y * s.y,
			m_LocalScale.z * s.z,
		};
	}
}

void GameObject::CheckSetOption(int Option, GameObject* Parent)
{
	if (Option & (int)SetParentOption::KeepPos)
	{
		D3DXMATRIX m = GetWorldMatrix();
		D3DXVECTOR3 thisPos = { m._41, m._42, m._43 };
		m = Parent->GetWorldMatrix();
		D3DXVECTOR3 parentPos = { m._41, m._42, m._43 };

		D3DXVECTOR3 pos = thisPos - parentPos;
		m_LocalPosition = pos.x * Parent->GetRight() + pos.y * Parent->GetUp() + pos.z * Parent->GetForward();
	}
	if (Option & (int)SetParentOption::KeepScale)
	{
		D3DXVECTOR3 s = Parent->GetWorldScale();
		m_LocalScale = {
			m_LocalScale.x / s.x,
			m_LocalScale.y / s.y,
			m_LocalScale.z / s.z,
		};
	}
}

/*******************************************************************************
*	デバッグ用関数
*******************************************************************************/
#ifdef _DEBUG
void GameObject::InitDebug()
{
	//-------------------
	// バッファ設定
	//-------------------
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(VERTEX_3D) * 2;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	VERTEX_3D* vertex = new VERTEX_3D[2];
	CreateVertex(vertex);

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	// バッファ生成
	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	// シェーダー設定
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "debugLineVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "debugLinePS.cso");
}

void GameObject::UninitDebug()
{
	m_VertexBuffer->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
	m_VertexLayout->Release();
}

void GameObject::DrawDebug()
{
	if (!DebugManager::m_IsParentLine || !m_Parent)
	{
		return;
	}

	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// ワールドマトリクス設定
	D3DXMATRIX world;
	world = Math::GetMatrixIdentity();
	Renderer::SetWorldMatrix(&world);

	// 頂点情報書き換え
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0,
		D3D11_MAP_WRITE_DISCARD, 0, &msr);
	CreateVertex((VERTEX_3D*)msr.pData);
	Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	Renderer::SetMaterial(material);

	// プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	// ポリゴン描画
	Renderer::GetDeviceContext()->Draw(2, 0);
}

void GameObject::CreateVertex(VERTEX_3D* Vertex)
{
	D3DXMATRIX thisMat = GetWorldMatrix();
	D3DXMATRIX parentMat;
	if (m_Parent)
	{
		parentMat = m_Parent->GetWorldMatrix();
	}
	else
	{
		parentMat = thisMat;
	}

	D3DXVECTOR3 n = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXCOLOR d = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	D3DXVECTOR2 c = D3DXVECTOR2(0.0f, 0.0f);

	Vertex[0].Position = D3DXVECTOR3(thisMat._41, thisMat._42, thisMat._43);
	Vertex[0].Normal = n;
	Vertex[0].Diffuse = d;
	Vertex[0].TexCoord = c;

	Vertex[1].Position = D3DXVECTOR3(parentMat._41, parentMat._42, parentMat._43);
	Vertex[1].Normal = n;
	Vertex[1].Diffuse = d;
	Vertex[1].TexCoord = c;
}
#endif
