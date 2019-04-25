#include "channelfactory.h"
#include "sportchannel.h"
#include "lifechannel.h"
#include "shoppingchannel.h"
#include "comedychannel.h"

Channel *ChannelFactory::MakeSportChannel()		{ return new SportChannel(); }
Channel *ChannelFactory::MakeLifeChannel()		{ return new LifeChannel(); }
Channel *ChannelFactory::MakeShoppingChannel()	{ return new ShoppingChannel(); }
Channel *ChannelFactory::MakeComedyChannel()	{ return new ComedyChannel(); }
