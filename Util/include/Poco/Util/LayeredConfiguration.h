//
// LayeredConfiguration.h
//
// $Id: //poco/Main/Util/include/Poco/Util/LayeredConfiguration.h#3 $
//
// Library: Util
// Package: Configuration
// Module:  LayeredConfiguration
//
// Definition of the LayeredConfiguration class.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef Util_LayeredConfiguration_INCLUDED
#define Util_LayeredConfiguration_INCLUDED


#include "Poco/Util/Util.h"
#include "Poco/Util/AbstractConfiguration.h"
#include "Poco/AutoPtr.h"
#include <list>


namespace Poco {
namespace Util {


class Util_API LayeredConfiguration: public AbstractConfiguration
	/// A LayeredConfiguration consists of a number of AbstractConfigurations.
	///
	/// When reading a configuration property in a LayeredConfiguration,
	/// all added configurations are searched, in order of their priority.
	/// Configurations with lower priority values have precedence.
	///
	/// When setting a property, the property is always written to the first writeable 
	/// configuration (see addWriteable()). 
	/// If no writeable configuration has been added to the LayeredConfiguration, and an
	/// attempt is made to set a property, a RuntimeException is thrown.
	///
	/// Every configuration added to the LayeredConfiguration has a priority value.
	/// The priority determines the position where the configuration is inserted,
	/// with lower priority values coming before higher priority values.
	///
	/// If no priority is specified, a priority of 0 is assumed.
{
public:
	LayeredConfiguration();
		/// Creates the LayeredConfiguration.
		
	void add(AbstractConfiguration* pConfig);
		/// Adds a read-only configuration to the back of the LayeredConfiguration.
		/// The LayeredConfiguration does not take ownership of the given
		/// configuration. In other words, the configuration's reference
		/// count is incremented.

	void add(AbstractConfiguration* pConfig, bool shared);
		/// Adds a read-only configuration to the back of the LayeredConfiguration.
		/// If shared is false, the LayeredConfiguration takes ownership
		/// of the given configuration (and the configuration's reference
		/// count remains unchanged).

	void add(AbstractConfiguration* pConfig, int priority);
		/// Adds a read-only configuration to the LayeredConfiguration.
		/// The LayeredConfiguration does not take ownership of the given
		/// configuration. In other words, the configuration's reference
		/// count is incremented.

	void add(AbstractConfiguration* pConfig, int priority, bool shared);
		/// Adds a read-only configuration the LayeredConfiguration.
		/// If shared is false, the LayeredConfiguration takes ownership
		/// of the given configuration (and the configuration's reference
		/// count remains unchanged).

	void add(AbstractConfiguration* pConfig, int priority, bool writeable, bool shared);
		/// Adds a configuration to the LayeredConfiguration.
		/// If shared is false, the LayeredConfiguration takes ownership
		/// of the given configuration (and the configuration's reference
		/// count remains unchanged).

	void addWriteable(AbstractConfiguration* pConfig, int priority);
		/// Adds a writeable configuration to the LayeredConfiguration.
		/// The LayeredConfiguration does not take ownership of the given
		/// configuration. In other words, the configuration's reference
		/// count is incremented.

	void addWriteable(AbstractConfiguration* pConfig, int priority, bool shared);
		/// Adds a writeable configuration to the LayeredConfiguration.
		/// If shared is false, the LayeredConfiguration takes ownership
		/// of the given configuration (and the configuration's reference
		/// count remains unchanged).

	//@ deprecated
	void addFront(AbstractConfiguration* pConfig);
		/// Adds a read-only configuration to the front of the LayeredConfiguration.
		/// The LayeredConfiguration does not take ownership of the given
		/// configuration. In other words, the configuration's reference
		/// count is incremented.

	//@ deprecated
	void addFront(AbstractConfiguration* pConfig, bool shared);
		/// Adds a read-only configuration to the front of the LayeredConfiguration.
		/// If shared is true, the LayeredConfiguration takes ownership
		/// of the given configuration.
		
protected:
	typedef Poco::AutoPtr<AbstractConfiguration> ConfigPtr;
	
	struct ConfigItem
	{
		ConfigPtr pConfig;
		int       priority;
		bool      writeable;
	};

	bool getRaw(const std::string& key, std::string& value) const;
	void setRaw(const std::string& key, const std::string& value);
	void enumerate(const std::string& key, Keys& range) const;
	
	int lowest() const;
	int highest() const;
	void insert(const ConfigItem& item);
	
	~LayeredConfiguration();

private:
	LayeredConfiguration(const LayeredConfiguration&);
	LayeredConfiguration& operator = (const LayeredConfiguration&);

	typedef std::list<ConfigItem> ConfigList;
	
	ConfigList _configs;
};


} } // namespace Poco::Util


#endif // Util_LayeredConfiguration_INCLUDED
