/* SPDX-License-Identifier: GPL-2.0 */

#ifndef _INTEL_PSH_IPC_H_
#define _INTEL_PSH_IPC_H_

#include <linux/bits.h>
#include <linux/types.h>

#define CHANNEL_BUSY		BIT(31)
#define PSH_IPC_CONTINUE	BIT(30)

struct psh_msg {
	u32 msg;
	u32 param;
};

int intel_ia2psh_command(struct psh_msg *in, struct psh_msg *out, int ch, int timeout);

enum psh_channel {
	/* IPC channels from host system to MCU */
	PSH_SEND_CH0		= 0,
	PSH_SEND_CH1		= 1,
	PSH_SEND_CH2		= 2,
	PSH_SEND_CH3		= 3,

	NUM_IA2PSH_IPC		= 4,

	/* IPC channels from MCU to host system */
	PSH_RECV_CH0		= 4,
	PSH_RECV_CH1		= 5,
	PSH_RECV_CH2		= 6,
	PSH_RECV_CH3		= 7,

	NUM_PSH2IA_IPC		= 4,

	NUM_ALL_CH = NUM_IA2PSH_IPC + NUM_PSH2IA_IPC,
};

typedef void (*psh_channel_handle_t)(u32 msg, u32 param, void *data);

int intel_psh_ipc_bind(int ch, psh_channel_handle_t handle, void *data);
void intel_psh_ipc_unbind(int ch);

void intel_psh_ipc_disable_irq(void);
void intel_psh_ipc_enable_irq(void);

#endif
