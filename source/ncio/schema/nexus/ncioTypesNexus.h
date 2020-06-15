/**
 * ncioTypesNexus.h : public header that defines specific NeXus types. This file
 * is installed in include/ncio/common
 *
 *  Created on: May 11, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#pragma once

#include <cstdint> //fixed-width types e.g. std::uint64_t

/**
 * Define inputs to NCIO API functions that are specific to the NeXus schema
 * types mapping to datasets or variables.
 * Info about the NeXus schema: https://manual.nexusformat.org/index.html
 */
namespace ncio::schema::nexus
{

#define NCIO_MACRO_NEXUS_TYPES(MACRO)                                          \
    MACRO(std::uint32_t)                                                       \
    MACRO(std::uint64_t)                                                       \
    MACRO(float)                                                               \
    MACRO(double)

#define NCIO_MACRO_FUNCTION_NEXUS_BANK_MAKE_ENUM(id)                           \
    enum class bank##id{event_id, event_index, event_time_offset,              \
                        event_time_zero, total_counts};

#define NCIO_MACRO_NEXUS_FOREACH_BANK_ID(MACRO)                                \
    MACRO(1)                                                                   \
    MACRO(2)                                                                   \
    MACRO(3)                                                                   \
    MACRO(4)                                                                   \
    MACRO(5)                                                                   \
    MACRO(6)                                                                   \
    MACRO(7)                                                                   \
    MACRO(8)                                                                   \
    MACRO(9)                                                                   \
    MACRO(10)                                                                  \
    MACRO(11)                                                                  \
    MACRO(12)                                                                  \
    MACRO(13)                                                                  \
    MACRO(14)                                                                  \
    MACRO(15)                                                                  \
    MACRO(16)                                                                  \
    MACRO(17)                                                                  \
    MACRO(18)                                                                  \
    MACRO(19)                                                                  \
    MACRO(20)                                                                  \
    MACRO(21)                                                                  \
    MACRO(22)                                                                  \
    MACRO(23)                                                                  \
    MACRO(24)                                                                  \
    MACRO(25)                                                                  \
    MACRO(26)                                                                  \
    MACRO(27)                                                                  \
    MACRO(28)                                                                  \
    MACRO(29)                                                                  \
    MACRO(30)                                                                  \
    MACRO(31)                                                                  \
    MACRO(32)                                                                  \
    MACRO(33)                                                                  \
    MACRO(34)                                                                  \
    MACRO(35)                                                                  \
    MACRO(36)                                                                  \
    MACRO(37)                                                                  \
    MACRO(38)                                                                  \
    MACRO(39)                                                                  \
    MACRO(40)                                                                  \
    MACRO(41)                                                                  \
    MACRO(42)                                                                  \
    MACRO(43)                                                                  \
    MACRO(44)                                                                  \
    MACRO(45)                                                                  \
    MACRO(46)                                                                  \
    MACRO(47)                                                                  \
    MACRO(48)                                                                  \
    MACRO(49)                                                                  \
    MACRO(50)                                                                  \
    MACRO(51)                                                                  \
    MACRO(52)                                                                  \
    MACRO(53)                                                                  \
    MACRO(54)                                                                  \
    MACRO(55)                                                                  \
    MACRO(56)                                                                  \
    MACRO(57)                                                                  \
    MACRO(58)                                                                  \
    MACRO(59)                                                                  \
    MACRO(60)                                                                  \
    MACRO(61)                                                                  \
    MACRO(62)                                                                  \
    MACRO(63)                                                                  \
    MACRO(64)                                                                  \
    MACRO(65)                                                                  \
    MACRO(66)                                                                  \
    MACRO(67)                                                                  \
    MACRO(68)                                                                  \
    MACRO(69)                                                                  \
    MACRO(70)                                                                  \
    MACRO(71)                                                                  \
    MACRO(72)                                                                  \
    MACRO(73)                                                                  \
    MACRO(74)                                                                  \
    MACRO(75)                                                                  \
    MACRO(76)                                                                  \
    MACRO(77)                                                                  \
    MACRO(78)                                                                  \
    MACRO(79)                                                                  \
    MACRO(80)                                                                  \
    MACRO(81)                                                                  \
    MACRO(82)                                                                  \
    MACRO(83)                                                                  \
    MACRO(84)                                                                  \
    MACRO(85)                                                                  \
    MACRO(86)                                                                  \
    MACRO(87)                                                                  \
    MACRO(88)                                                                  \
    MACRO(89)                                                                  \
    MACRO(90)                                                                  \
    MACRO(91)                                                                  \
    MACRO(92)                                                                  \
    MACRO(93)                                                                  \
    MACRO(94)                                                                  \
    MACRO(95)                                                                  \
    MACRO(96)                                                                  \
    MACRO(97)                                                                  \
    MACRO(98)                                                                  \
    MACRO(99)                                                                  \
    MACRO(100)                                                                 \
    MACRO(101)                                                                 \
    MACRO(102)                                                                 \
    MACRO(103)                                                                 \
    MACRO(104)                                                                 \
    MACRO(105)                                                                 \
    MACRO(106)                                                                 \
    MACRO(107)                                                                 \
    MACRO(108)                                                                 \
    MACRO(109)                                                                 \
    MACRO(110)                                                                 \
    MACRO(111)                                                                 \
    MACRO(112)                                                                 \
    MACRO(113)                                                                 \
    MACRO(114)                                                                 \
    MACRO(115)                                                                 \
    MACRO(116)                                                                 \
    MACRO(117)                                                                 \
    MACRO(118)                                                                 \
    MACRO(119)                                                                 \
    MACRO(120)                                                                 \
    MACRO(121)                                                                 \
    MACRO(122)                                                                 \
    MACRO(123)                                                                 \
    MACRO(124)                                                                 \
    MACRO(125)                                                                 \
    MACRO(126)                                                                 \
    MACRO(127)                                                                 \
    MACRO(128)                                                                 \
    MACRO(129)                                                                 \
    MACRO(130)                                                                 \
    MACRO(131)                                                                 \
    MACRO(132)                                                                 \
    MACRO(133)                                                                 \
    MACRO(134)                                                                 \
    MACRO(135)                                                                 \
    MACRO(136)                                                                 \
    MACRO(137)                                                                 \
    MACRO(138)                                                                 \
    MACRO(139)                                                                 \
    MACRO(140)                                                                 \
    MACRO(141)                                                                 \
    MACRO(142)                                                                 \
    MACRO(143)                                                                 \
    MACRO(144)                                                                 \
    MACRO(145)                                                                 \
    MACRO(146)                                                                 \
    MACRO(147)                                                                 \
    MACRO(148)                                                                 \
    MACRO(149)                                                                 \
    MACRO(150)                                                                 \
    MACRO(151)                                                                 \
    MACRO(152)                                                                 \
    MACRO(153)                                                                 \
    MACRO(154)                                                                 \
    MACRO(155)                                                                 \
    MACRO(156)                                                                 \
    MACRO(157)                                                                 \
    MACRO(158)                                                                 \
    MACRO(159)                                                                 \
    MACRO(160)                                                                 \
    MACRO(161)                                                                 \
    MACRO(162)                                                                 \
    MACRO(163)                                                                 \
    MACRO(164)                                                                 \
    MACRO(165)                                                                 \
    MACRO(166)                                                                 \
    MACRO(167)                                                                 \
    MACRO(168)                                                                 \
    MACRO(169)                                                                 \
    MACRO(170)                                                                 \
    MACRO(171)                                                                 \
    MACRO(172)                                                                 \
    MACRO(173)                                                                 \
    MACRO(174)                                                                 \
    MACRO(175)                                                                 \
    MACRO(176)                                                                 \
    MACRO(177)                                                                 \
    MACRO(178)                                                                 \
    MACRO(179)                                                                 \
    MACRO(180)                                                                 \
    MACRO(181)                                                                 \
    MACRO(182)                                                                 \
    MACRO(183)                                                                 \
    MACRO(184)                                                                 \
    MACRO(185)                                                                 \
    MACRO(186)                                                                 \
    MACRO(187)                                                                 \
    MACRO(188)                                                                 \
    MACRO(189)                                                                 \
    MACRO(190)                                                                 \
    MACRO(191)                                                                 \
    MACRO(192)                                                                 \
    MACRO(193)                                                                 \
    MACRO(194)                                                                 \
    MACRO(195)                                                                 \
    MACRO(196)                                                                 \
    MACRO(197)                                                                 \
    MACRO(198)                                                                 \
    MACRO(199)                                                                 \
    MACRO(200)                                                                 \
    MACRO(201)                                                                 \
    MACRO(202)                                                                 \
    MACRO(203)                                                                 \
    MACRO(204)                                                                 \
    MACRO(205)                                                                 \
    MACRO(206)                                                                 \
    MACRO(207)                                                                 \
    MACRO(208)                                                                 \
    MACRO(209)                                                                 \
    MACRO(210)                                                                 \
    MACRO(211)                                                                 \
    MACRO(212)                                                                 \
    MACRO(213)                                                                 \
    MACRO(214)                                                                 \
    MACRO(215)                                                                 \
    MACRO(216)                                                                 \
    MACRO(217)                                                                 \
    MACRO(218)                                                                 \
    MACRO(219)                                                                 \
    MACRO(220)                                                                 \
    MACRO(221)                                                                 \
    MACRO(222)                                                                 \
    MACRO(223)                                                                 \
    MACRO(224)                                                                 \
    MACRO(225)                                                                 \
    MACRO(226)                                                                 \
    MACRO(227)                                                                 \
    MACRO(228)                                                                 \
    MACRO(229)                                                                 \
    MACRO(230)                                                                 \
    MACRO(231)                                                                 \
    MACRO(232)                                                                 \
    MACRO(233)                                                                 \
    MACRO(234)                                                                 \
    MACRO(235)                                                                 \
    MACRO(236)                                                                 \
    MACRO(237)                                                                 \
    MACRO(238)                                                                 \
    MACRO(239)                                                                 \
    MACRO(240)                                                                 \
    MACRO(241)                                                                 \
    MACRO(242)                                                                 \
    MACRO(243)                                                                 \
    MACRO(244)                                                                 \
    MACRO(245)                                                                 \
    MACRO(246)                                                                 \
    MACRO(247)                                                                 \
    MACRO(248)                                                                 \
    MACRO(249)                                                                 \
    MACRO(250)                                                                 \
    MACRO(251)                                                                 \
    MACRO(252)                                                                 \
    MACRO(253)                                                                 \
    MACRO(254)                                                                 \
    MACRO(255)                                                                 \
    MACRO(256)                                                                 \
    MACRO(_error)                                                              \
    MACRO(_unmapped)

#define declare_nexus_banks_enum_entries(T)                                    \
    NCIO_MACRO_FUNCTION_NEXUS_BANK_MAKE_ENUM(T)

NCIO_MACRO_NEXUS_FOREACH_BANK_ID(declare_nexus_banks_enum_entries)
#undef declare_nexus_banks_enum_entries

enum class log
{
    average_value,
    average_value_error,
    device_id,
    device_name,
    maximum_value,
    minimum_value,
    time,
    value
};

enum class sample
{
    can_barcode,
    can_indicator,
    can_materials,
    can_name,
    chemical_formula,
    comments,
    component,
    container_id,
    container_name,
    description,
    height_in_container,
    identifier,
    interior_depth,
    interior_diameter,
    interior_height,
    interior_width,
    lattice_a,
    lattice_alpha,
    lattice_b,
    lattice_beta,
    lattice_c,
    lattice_gamma,
    mass,
    mass_density,
    name,
    nature,
    outer_depth,
    outer_diameter,
    outer_height,
    outer_width,
    volume_cubic
};

enum class user
{
    facility_user_id,
    name
};

} // end namespace ncio::nexus
