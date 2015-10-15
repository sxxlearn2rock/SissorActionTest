#include "ProcessorFactory.h"



DenoiseProcessor* DenoiseProcessorFactory::createDenoiseProcessor(DenoiseProcType type)
{
	DenoiseProcessor* denoiseProcessor = NULL;
	switch(type)
	{
	case DEFAULT:
		denoiseProcessor = new DefaultDenosieProcessor;
		break;
	}

	return denoiseProcessor;
}
