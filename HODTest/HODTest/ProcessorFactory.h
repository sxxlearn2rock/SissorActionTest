#pragma once
#include "DenoiseStrategy.h"
#include "DenoiseProcessor.h"
#include "strategies.h"

enum DenoiseProcType {DEFAULT};

class DenoiseProcessorFactory
{
public:
	DenoiseProcessorFactory(void) {}
	~DenoiseProcessorFactory(void) {}

	DenoiseProcessor* createDenoiseProcessor(DenoiseProcType type);
};
