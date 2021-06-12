//
//  ALCUserClient.hpp
//  AppleALC
//
//  Created by Nick on 10/14/20.
//  Copyright © 2020 vit9696. All rights reserved.
//

#ifndef ALCUserClient_hpp
#define ALCUserClient_hpp

#include <IOKit/IOService.h>
#include <IOKit/IOUserClient.h>

#include "UserKernelShared.h"
#include "ALCUserClientProvider.hpp"

class EXPORT ALCUserClient : public IOUserClient {
	using super = IOUserClient;
	OSDeclareDefaultStructors(ALCUserClient);

	ALCUserClientProvider* mProvider { nullptr };
	task_t mTask {nullptr};
	static const IOExternalMethodDispatch sMethods[kNumberOfMethods];
	
public:
	virtual bool start(IOService* provider) override;
	
	virtual bool initWithTask(task_t owningTask, void* securityToken,
							  UInt32 type, OSDictionary* properties) override;

	virtual IOReturn clientClose() override;
	virtual IOReturn externalMethod(uint32_t selector, IOExternalMethodArguments* arguments,
									IOExternalMethodDispatch* dispatch, OSObject* target,
									void* reference) override;
	
protected:
	static IOReturn methodExecuteVerb(ALCUserClientProvider* target, void* ref,
									  IOExternalMethodArguments* args);
};

#endif /* ALCUserClient_hpp */
