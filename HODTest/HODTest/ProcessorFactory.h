#pragma once
#include "DenoiseProcessor.h"
#include "DefaultDenoiseProcessor.h"

enum DenoiseProcType {DEFAULT};

class DenoiseProcessorFactory
{
public:
	DenoiseProcessorFactory(void) {}
	~DenoiseProcessorFactory(void) {}

	DenoiseProcessor* createDenoiseProcessor(DenoiseProcType type);
};
