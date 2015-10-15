#pragma once
#include "DenoiseProcessors.h"
#include "SegmentProcessors.h"
#include "RecogniseProcessors.h"

enum DenoiseProcType {DEFAULT};

class DenoiseProcessorFactory
{
public:
	DenoiseProcessorFactory(void) {}
	~DenoiseProcessorFactory(void) {}

	DenoiseProcessor* createDenoiseProcessor(DenoiseProcType type);
};

class SegmentProcessorFactory
{
public:
	SegmentProcessorFactory(void) {}
	~SegmentProcessorFactory(void) {}

	SegmentProcessor* createSegmentProcessor();
};

class RecogniseProcessorFactory
{
public:
	RecogniseProcessorFactory(void) {}
	~RecogniseProcessorFactory(void) {}

	RecogniseProcessor* createRecogniseProcessor();
};