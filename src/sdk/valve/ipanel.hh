//
//  ruvi base
//

// includes
#include "sdk/memory/memory.hh"

class i_panel {
public:
	const char *get_name(unsigned long long vgui_panel) {
		return memory::vfunc<37, const char *>(this, vgui_panel);
	}
};
