#include "../LUA/LuaUserData.h"

//enum InterfaceState
//{
//	MENU = 2,
//	SERVER = 1,
//	CLIENT = 0
//};

//enum
//{
//	SPECIAL_GLOB,		// Global table
//	SPECIAL_ENV,		// Environment table
//	SPECIAL_REG,		// Registry table
//};
//
//namespace Type
//{
//	enum
//	{
//		INVALID = -1,
//		NIL,
//		BOOL,
//		LIGHTUSERDATA,
//		NUMBER,
//		STRING,
//		TABLE,
//		FUNCTION,
//		USERDATA,
//		THREAD,
//
//		// UserData
//		ENTITY,
//		VECTOR,
//		ANGLE,
//		PHYSOBJ,
//		SAVE,
//		RESTORE,
//		DAMAGEINFO,
//		EFFECTDATA,
//		MOVEDATA,
//		RECIPIENTFILTER,
//		USERCMD,
//		SCRIPTEDVEHICLE,
//
//		// Client Only
//		MATERIAL,
//		PANEL,
//		PARTICLE,
//		PARTICLEEMITTER,
//		TEXTURE,
//		USERMSG,
//
//		CONVAR,
//		IMESH,
//		MATRIX,
//		SOUND,
//		PIXELVISHANDLE,
//		DLIGHT,
//		VIDEO,
//		FILE,
//
//		COUNT
//	};
//}

//struct UserData
//{
//	void* data;
//	unsigned char	type;
//};

typedef int(*CLuaFunction) (lua_State*);

class ILuaObject
{
public:
	//1
	virtual void            Set(ILuaObject* obj) = 0;
	virtual void            SetFromStack(int i) = 0;
	virtual void            UnReference() = 0;
	virtual int             GetType(void) = 0;
	virtual const char*     GetString(void) = 0;
	//2
	virtual float           GetFloat(void) = 0;
	virtual int             GetInt(void) = 0;
	virtual void*			GetUserData(void) = 0;
	virtual void            SetMember(const char* name) = 0;
	virtual void            SetMember(const char* name, ILuaObject* obj) = 0; // ( This is also used to set nil by passing NULL )
	//3
	virtual void            SetMember(const char* name, float val) = 0;
	virtual void            SetMember(const char* name, bool val) = 0;
	virtual void            SetMember(const char* name, const char* val) = 0;
	virtual void            SetMember(const char* name, CLuaFunction f) = 0;
	virtual bool            GetMemberBool(const char* name, bool b = true) = 0;
	//4
	virtual int                GetMemberInt(const char* name, int i = 0) = 0;
	virtual float            GetMemberFloat(const char* name, float f = 0.0f) = 0;
	virtual const char* GetMemberStr(const char* name, const char* = "") = 0;
	virtual void* GetMemberUserData(const char* name, void* = 0) = 0;
	virtual void* GetMemberUserData(float name, void* = 0) = 0;
	//5
	virtual ILuaObject* GetMember(const char* name) = 0;
	virtual ILuaObject* GetMember(ILuaObject*) = 0;
	virtual void            SetMetaTable(ILuaObject* obj) = 0;
	virtual void            SetUserData(void* obj) = 0;
	virtual void            Push(void) = 0;
	//6
	virtual bool            isNil() = 0;
	virtual bool            isTable() = 0;
	virtual bool            isString() = 0;
	virtual bool            isNumber() = 0;
	virtual bool            isFunction() = 0;
	virtual bool            isUserData() = 0;
	virtual ILuaObject* GetMember(float fKey) = 0;
	virtual void* Remove_Me_1(const char* name, void* = 0) = 0;
	virtual void            SetMember(float fKey) = 0;
	virtual void            SetMember(float fKey, ILuaObject* obj) = 0;
	virtual void            SetMember(float fKey, float val) = 0;
	virtual void            SetMember(float fKey, bool val) = 0;
	virtual void            SetMember(float fKey, const char* val) = 0;
	virtual void            SetMember(float fKey, CLuaFunction f) = 0;
	virtual const char* GetMemberStr(float name, const char* = "") = 0;
	virtual void            SetMember(ILuaObject* k, ILuaObject* v) = 0;
	virtual bool            GetBool(void) = 0;
	virtual bool            PushMemberFast(int iStackPos) = 0;
	virtual void            SetMemberFast(int iKey, int iValue) = 0;

	virtual void            SetFloat(float val) = 0;
	virtual void            SetString(const char* val) = 0;
	virtual double            GetDouble(void) = 0;

	virtual void            SetMember_FixKey(char  const*, float) = 0;
	virtual void            SetMember_FixKey(char  const*, char  const*) = 0;
	virtual void            SetMember_FixKey(char  const*, ILuaObject*) = 0;

	virtual bool            isBool(void) = 0;
	virtual void            SetMemberDouble(char  const*, double) = 0;
	virtual void            SetMemberNil(char  const*) = 0;
	virtual void            SetMemberNil(float) = 0;

	virtual bool            Debug_IsUnreferenced() = 0;

	virtual void            Init(void) = 0;
	virtual void            SetFromGlobal(char  const*) = 0;

	virtual void            SetMember(char  const*, unsigned long long) = 0;
	virtual void            SetReference(int i) = 0;

	virtual void            RemoveMember(char  const*) = 0;
	virtual void            RemoveMember(float) = 0;
	virtual bool            MemberIsNil(char  const*) = 0;

	virtual void            SetMemberDouble(float, double) = 0;
	virtual double            GetMemberDouble(char  const*, double) = 0;
};
