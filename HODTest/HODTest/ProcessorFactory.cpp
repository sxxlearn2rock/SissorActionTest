#include "ProcessorFactory.h"



DenoiseProcessor* DenoiseProcessorFactory::createDenoiseProcessor(DenoiseProcType type)
{
	DenoiseProcessor* denoiseProcessor = NULL;
	switch(type)
	{
	case DEFAULT:
		denoiseProcessor = new DenoiseProcessor(DefaultDenosieStrategy::getInstance());
		break;
	}

	return denoiseProcessor;
}
