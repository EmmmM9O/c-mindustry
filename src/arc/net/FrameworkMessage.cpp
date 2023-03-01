#pragma once

namespace arc {
    namespace net {
        namespace FrameworkMessage{
            class _FrameworkMessage_{

            };
            class KeepAlive:public _FrameworkMessage_{

            };
            const KeepAlive keepAlive;
            class RegisterTCP:public _FrameworkMessage_{
                public:
                int connectionID;
            };
            class RegisterUDP:public _FrameworkMessage_{
                public:
                int connectionID;
            };
        };
    }
}