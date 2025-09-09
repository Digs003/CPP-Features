class Base
{
public:
	int m_public {};
protected:
	int m_protected {};
private:
	int m_private {};
};

class D2 : private Base // note: private inheritance
{
	// Private inheritance means:
	// Public inherited members become private
	// Protected inherited members become private
	// Private inherited members stay inaccessible
public:
	int m_public2 {};
protected:
	int m_protected2 {};
private:
	int m_private2 {};
};

// D2 can access its own members without restriction. D2 can access Base’s m_public and m_protected members, but not m_private.
// Because D2 inherited Base privately, m_public and m_protected are now considered private when accessed through D2.
// This means the public can not access these variables when using a D2 object, nor can any classes derived from D2.

class D3 : public D2
{
	// Public inheritance means:
	// Public inherited members stay public
	// Protected inherited members stay protected
	// Private inherited members stay inaccessible
public:
	int m_public3 {};
protected:
	int m_protected3 {};
private:
	int m_private3 {};
};


// D3 can access its own members without restriction. D3 can access D2’s m_public2 and m_protected2 members, but not m_private2.
// Because D3 inherited D2 publicly, m_public2 and m_protected2 keep their access specifiers when accessed through D3. 
// D3 has no access to Base’s m_private, which was already private in Base. Nor does it have access to Base’s m_protected or m_public, both of which became private when D2 inherited them.

