/*
 * preferences.h
 * Preferences storage heavily insipired by the SharedPreferences in Android
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace utils
{
namespace io
{

class Preferences final
{
public:
	enum struct TypeId
	{
		kBool = 0,
		kFloat,
		kInt,
		kLong,
		kString,
		kStringSet
	};

	template<typename T>
	struct TypeTrait
	{
		static constexpr TypeId Id();
	};

	struct Object
	{
		virtual ~Object()
		{}

		virtual TypeId GetTypeId() const = 0;
		virtual Object* Clone() const = 0;
	};

	class Editor final
	{
	public:
		explicit Editor(Preferences *pref);

		void Clear();
		/**
		 * Commit the changes, if you no longer use this Editor afterwards,
		 * invoke CommitAndInvalidate() instead which can save a bunch of
		 * copying
		 */
		void Commit();
		/**
		 * Commit the changes and invalidate this Editor object. Must NOT use
		 * this object afterwards
		 */
		void CommitAndInvalidate();

		Editor& PutBool(const std::wstring &key, const bool value);
		Editor& PutFloat(const std::wstring &key, const float value);
		Editor& PutLong(const std::wstring &key, const long value);
		Editor& PutInt(const std::wstring &key, const int value);
		Editor& PutString(const std::wstring &key,
				const std::wstring &value);
		Editor& PutString(const std::wstring &key, std::wstring &&value);
		Editor& PutStringSet(const std::wstring &key,
				const std::vector<std::wstring> &value);
		Editor& PutStringSet(const std::wstring &key,
				std::vector<std::wstring> &&value);

		void Remove(const std::wstring &key);

	private:
		Preferences *m_pref;
		std::map<std::wstring, std::unique_ptr<Object>> m_map;
	};

	class Loader
	{
	public:
		virtual ~Loader()
		{}

		virtual bool Load(const std::unique_ptr<Editor> &edit) = 0;
	};

	class Writer
	{
	public:
		virtual ~Writer()
		{}

		virtual void StartWrite() = 0;
		virtual void EndWrite() = 0;
		virtual void Write(const std::wstring &key, const bool value) = 0;
		virtual void Write(const std::wstring &key, const float value) = 0;
		virtual void Write(const std::wstring &key, const int value) = 0;
		virtual void Write(const std::wstring &key, const long value) = 0;
		virtual void Write(const std::wstring &key, const std::wstring &value) = 0;
		virtual void Write(const std::wstring &key,
				const std::vector<std::wstring> &value) = 0;
	};

	/**
	 * Construct a preferences with supplied Loader and Writer, since this class
	 * does not claim ownership, you have to ensure the lifetime of the two are
	 * sufficient. To be precise, @a loader must be valid until returning from
	 * this constructor; @a writer must be valid until destructing this class
	 *
	 * @param loader Optional Loader to load the preferences data
	 * @param writer Optional Writer to be used during commit
	 */
	Preferences(Loader *loader, Writer *writer);

	bool Contains(const std::wstring &key) const;
	std::unique_ptr<Editor> Edit();

	/**
	 * Retrieve all values from the preferences. Note that you must not modify
	 * the collection returned by this method, or alter any of its contents. The
	 * consistency of your stored data is not guaranteed if you do
	 *
	 * @return Returns a map containing a list of pairs key/value representing
	 * the preferences
	 */
	const std::map<std::wstring, std::unique_ptr<Object>>& GetAll() const;
	bool GetBool(const std::wstring &key, const bool def_value) const;
	float GetFloat(const std::wstring &key, const float def_value) const;
	int GetInt(const std::wstring &key, const int def_value) const;
	long GetLong(const std::wstring &key, const long def_value) const;
	std::wstring GetString(const std::wstring &key, std::wstring &&def_value) const;
	const std::wstring* GetString(const std::wstring &key) const;
	std::vector<std::wstring> GetStringSet(const std::wstring &key,
			std::vector<std::wstring> &&def_value) const;
	const std::vector<std::wstring>* GetStringSet(const std::wstring &key) const;

private:
	template<typename T>
	T GetPrimitive(const std::wstring &key, const T def_value) const;
	template<typename T>
	T GetObject(const std::wstring &key, T &&def_value) const;
	template<typename T>
	const T* GetObject(const std::wstring &key) const;

	void Commit(const std::map<std::wstring, std::unique_ptr<Object>> &map);
	void Commit(std::map<std::wstring, std::unique_ptr<Object>> &&map);
	void Write();

	std::map<std::wstring, std::unique_ptr<Object>> m_map;

	bool m_is_init;
	Writer *m_writer;
};

}
}
