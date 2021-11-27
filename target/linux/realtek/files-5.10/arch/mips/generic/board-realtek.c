// SPDX-License-Identifier: GPL-2.0-only
/*
 * Board detection for the Realtek RTL838X, RTL839X, RTL930X, RTL931X SoCs
 *
 * based on the original BSP by
 * Copyright (C) 2006-2012 Tony Wu (tonywu@realtek.com)
 * Copyright (C) 2020 B. Koblitz
 *
 */

#include <asm/bootinfo.h>
#include <asm/machine.h>

#include <asm/mach-rtl838x/mach-rtl83xx.h>

struct rtl83xx_soc_info soc_info;

static __init void identify_rtl9302(u32 model)
{
	switch (model & 0xfffffff0) {
	case 0x93020810:
		soc_info.name = "RTL9302A 12x2.5G";
		break;
	case 0x93021010:
		soc_info.name = "RTL9302B 8x2.5G";
		break;
	case 0x93021810:
		soc_info.name = "RTL9302C 16x2.5G";
		break;
	case 0x93022010:
		soc_info.name = "RTL9302D 24x2.5G";
		break;
	case 0x93020800:
		soc_info.name = "RTL9302A";
		break;
	case 0x93021000:
		soc_info.name = "RTL9302B";
		break;
	case 0x93021800:
		soc_info.name = "RTL9302C";
		break;
	case 0x93022000:
		soc_info.name = "RTL9302D";
		break;
	case 0x93023001:
		soc_info.name = "RTL9302F";
		break;
	default:
		soc_info.name = "RTL9302";
	}
}

static __init void realtek_detect(u32 info_addr)
{
	u32 model;

	model = sw_r32(info_addr);
	soc_info.id = model >> 16 & 0xFFFF;

	switch (soc_info.id) {
	case 0x8328:
		soc_info.name = "RTL8328";
		soc_info.family = RTL8328_FAMILY_ID;
		break;
	case 0x8332:
		soc_info.name = "RTL8332";
		soc_info.family = RTL8380_FAMILY_ID;
		break;
	case 0x8380:
		soc_info.name = "RTL8380";
		soc_info.family = RTL8380_FAMILY_ID;
		break;
	case 0x8382:
		soc_info.name = "RTL8382";
		soc_info.family = RTL8380_FAMILY_ID;
		break;
	case 0x8390:
		soc_info.name = "RTL8390";
		soc_info.family = RTL8390_FAMILY_ID;
		break;
	case 0x8391:
		soc_info.name = "RTL8391";
		soc_info.family = RTL8390_FAMILY_ID;
		break;
	case 0x8392:
		soc_info.name = "RTL8392";
		soc_info.family = RTL8390_FAMILY_ID;
		break;
	case 0x8393:
		soc_info.name = "RTL8393";
		soc_info.family = RTL8390_FAMILY_ID;
		break;
	case 0x9301:
		soc_info.name = "RTL9301";
		soc_info.family = RTL9300_FAMILY_ID;
		break;
	case 0x9302:
		identify_rtl9302(model);
		soc_info.family = RTL9300_FAMILY_ID;
		break;
	case 0x9313:
		soc_info.name = "RTL9313";
		soc_info.family = RTL9310_FAMILY_ID;
		break;
	default:
		soc_info.name = "DEFAULT";
		soc_info.family = 0;
	}

	system_type = soc_info.name;
}

static __init const void *realtek_fixup_fdt(const void *fdt, const void *match_data)
{
	realtek_detect((u32) match_data);

	return fdt;
}

static const struct of_device_id realtek_board_ids[] = {
	/* Downstream compatibles */
	{
		.compatible = "realtek,rtl838x-soc",
		.data = (const void *)RTL838X_MODEL_NAME_INFO,
	},
	{
		.compatible = "realtek,rtl839x-soc",
		.data = (const void *)RTL839X_MODEL_NAME_INFO,
	},
	{
		.compatible = "realtek,rtl93xx-soc",
		.data = (const void *)RTL93XX_MODEL_NAME_INFO,
	},
	/* Upstream compatibles */
	{
		.compatible = "realtek,rtl8382-soc",
		.data = (const void *)RTL838X_MODEL_NAME_INFO,
	},
	{ /* sentinel */ }
};

MIPS_MACHINE(realtek) = {
	.matches = realtek_board_ids,
	.fixup_fdt = realtek_fixup_fdt,
};
