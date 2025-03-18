#pragma once

class UEngineStatics
{
public:
    static uint GenUUID()
    {
        return NextUUID++;
    }

private:
    static uint NextUUID;
};
