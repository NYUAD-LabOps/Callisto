/* generated HAL source file - do not edit */
#include "hal_data.h"
#if (0) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_external_irqAB) && !defined(SSP_SUPPRESS_ISR_ICU15)
SSP_VECTOR_DEFINE(icu_irq_isr, ICU, IRQ15);
#endif
#endif
static icu_instance_ctrl_t g_external_irqAB_ctrl;
static const external_irq_cfg_t g_external_irqAB_cfg =
{ .channel = 15,
  .trigger = EXTERNAL_IRQ_TRIG_BOTH_EDGE,
  .filter_enable = true,
  .pclk_div = EXTERNAL_IRQ_PCLK_DIV_BY_64,
  .autostart = true,
  .p_callback = g_external_irqAB_callback,
  .p_context = &g_external_irqAB,
  .p_extend = NULL,
  .irq_ipl = (0), };
/* Instance structure to use this module. */
const external_irq_instance_t g_external_irqAB =
{ .p_ctrl = &g_external_irqAB_ctrl, .p_cfg = &g_external_irqAB_cfg, .p_api = &g_external_irq_on_icu };
#if (0) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_external_irqAA) && !defined(SSP_SUPPRESS_ISR_ICU10)
SSP_VECTOR_DEFINE(icu_irq_isr, ICU, IRQ10);
#endif
#endif
static icu_instance_ctrl_t g_external_irqAA_ctrl;
static const external_irq_cfg_t g_external_irqAA_cfg =
{ .channel = 10,
  .trigger = EXTERNAL_IRQ_TRIG_BOTH_EDGE,
  .filter_enable = true,
  .pclk_div = EXTERNAL_IRQ_PCLK_DIV_BY_64,
  .autostart = true,
  .p_callback = g_external_irqAA_callback,
  .p_context = &g_external_irqAA,
  .p_extend = NULL,
  .irq_ipl = (0), };
/* Instance structure to use this module. */
const external_irq_instance_t g_external_irqAA =
{ .p_ctrl = &g_external_irqAA_ctrl, .p_cfg = &g_external_irqAA_cfg, .p_api = &g_external_irq_on_icu };
#if (0) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_external_irqYB) && !defined(SSP_SUPPRESS_ISR_ICU9)
SSP_VECTOR_DEFINE(icu_irq_isr, ICU, IRQ9);
#endif
#endif
static icu_instance_ctrl_t g_external_irqYB_ctrl;
static const external_irq_cfg_t g_external_irqYB_cfg =
{ .channel = 9,
  .trigger = EXTERNAL_IRQ_TRIG_BOTH_EDGE,
  .filter_enable = true,
  .pclk_div = EXTERNAL_IRQ_PCLK_DIV_BY_64,
  .autostart = true,
  .p_callback = g_external_irqYB_callback,
  .p_context = &g_external_irqYB,
  .p_extend = NULL,
  .irq_ipl = (0), };
/* Instance structure to use this module. */
const external_irq_instance_t g_external_irqYB =
{ .p_ctrl = &g_external_irqYB_ctrl, .p_cfg = &g_external_irqYB_cfg, .p_api = &g_external_irq_on_icu };
#if (0) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_external_irqYA) && !defined(SSP_SUPPRESS_ISR_ICU11)
SSP_VECTOR_DEFINE(icu_irq_isr, ICU, IRQ11);
#endif
#endif
static icu_instance_ctrl_t g_external_irqYA_ctrl;
static const external_irq_cfg_t g_external_irqYA_cfg =
{ .channel = 11,
  .trigger = EXTERNAL_IRQ_TRIG_BOTH_EDGE,
  .filter_enable = true,
  .pclk_div = EXTERNAL_IRQ_PCLK_DIV_BY_64,
  .autostart = true,
  .p_callback = g_external_irqYA_callback,
  .p_context = &g_external_irqYA,
  .p_extend = NULL,
  .irq_ipl = (0), };
/* Instance structure to use this module. */
const external_irq_instance_t g_external_irqYA =
{ .p_ctrl = &g_external_irqYA_ctrl, .p_cfg = &g_external_irqYA_cfg, .p_api = &g_external_irq_on_icu };
#if (0) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_external_irqXB) && !defined(SSP_SUPPRESS_ISR_ICU13)
SSP_VECTOR_DEFINE(icu_irq_isr, ICU, IRQ13);
#endif
#endif
static icu_instance_ctrl_t g_external_irqXB_ctrl;
static const external_irq_cfg_t g_external_irqXB_cfg =
{ .channel = 13,
  .trigger = EXTERNAL_IRQ_TRIG_BOTH_EDGE,
  .filter_enable = true,
  .pclk_div = EXTERNAL_IRQ_PCLK_DIV_BY_64,
  .autostart = true,
  .p_callback = g_external_irqXB_callback,
  .p_context = &g_external_irqXB,
  .p_extend = NULL,
  .irq_ipl = (0), };
/* Instance structure to use this module. */
const external_irq_instance_t g_external_irqXB =
{ .p_ctrl = &g_external_irqXB_ctrl, .p_cfg = &g_external_irqXB_cfg, .p_api = &g_external_irq_on_icu };
#if (0) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_external_irqXA) && !defined(SSP_SUPPRESS_ISR_ICU12)
SSP_VECTOR_DEFINE(icu_irq_isr, ICU, IRQ12);
#endif
#endif
static icu_instance_ctrl_t g_external_irqXA_ctrl;
static const external_irq_cfg_t g_external_irqXA_cfg =
{ .channel = 12,
  .trigger = EXTERNAL_IRQ_TRIG_BOTH_EDGE,
  .filter_enable = true,
  .pclk_div = EXTERNAL_IRQ_PCLK_DIV_BY_64,
  .autostart = true,
  .p_callback = g_external_irqXA_callback,
  .p_context = &g_external_irqXA,
  .p_extend = NULL,
  .irq_ipl = (0), };
/* Instance structure to use this module. */
const external_irq_instance_t g_external_irqXA =
{ .p_ctrl = &g_external_irqXA_ctrl, .p_cfg = &g_external_irqXA_cfg, .p_api = &g_external_irq_on_icu };
#if (0) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_timerT) && !defined(SSP_SUPPRESS_ISR_GPT9)
SSP_VECTOR_DEFINE_CHAN(gpt_counter_overflow_isr, GPT, COUNTER_OVERFLOW, 9);
#endif
#endif
static gpt_instance_ctrl_t g_timerT_ctrl;
static const timer_on_gpt_cfg_t g_timerT_extend =
{ .gtioca =
{ .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .gtiocb =
  { .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .shortest_pwm_signal = GPT_SHORTEST_LEVEL_OFF, };
static const timer_cfg_t g_timerT_cfg =
{ .mode = TIMER_MODE_PERIODIC, .period = 10, .unit = TIMER_UNIT_PERIOD_MSEC, .duty_cycle = 50, .duty_cycle_unit =
          TIMER_PWM_UNIT_RAW_COUNTS,
  .channel = 9, .autostart = false, .p_callback = gpt_MotorT_callback, .p_context = &g_timerT, .p_extend =
          &g_timerT_extend,
  .irq_ipl = (0), };
/* Instance structure to use this module. */
const timer_instance_t g_timerT =
{ .p_ctrl = &g_timerT_ctrl, .p_cfg = &g_timerT_cfg, .p_api = &g_timer_on_gpt };
#if (0) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_timerD) && !defined(SSP_SUPPRESS_ISR_GPT8)
SSP_VECTOR_DEFINE_CHAN(gpt_counter_overflow_isr, GPT, COUNTER_OVERFLOW, 8);
#endif
#endif
static gpt_instance_ctrl_t g_timerD_ctrl;
static const timer_on_gpt_cfg_t g_timerD_extend =
{ .gtioca =
{ .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .gtiocb =
  { .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .shortest_pwm_signal = GPT_SHORTEST_LEVEL_OFF, };
static const timer_cfg_t g_timerD_cfg =
{ .mode = TIMER_MODE_PERIODIC, .period = 10, .unit = TIMER_UNIT_PERIOD_MSEC, .duty_cycle = 50, .duty_cycle_unit =
          TIMER_PWM_UNIT_RAW_COUNTS,
  .channel = 8, .autostart = false, .p_callback = gpt_MotorD_callback, .p_context = &g_timerD, .p_extend =
          &g_timerD_extend,
  .irq_ipl = (0), };
/* Instance structure to use this module. */
const timer_instance_t g_timerD =
{ .p_ctrl = &g_timerD_ctrl, .p_cfg = &g_timerD_cfg, .p_api = &g_timer_on_gpt };
#if (0) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_timerC) && !defined(SSP_SUPPRESS_ISR_GPT6)
SSP_VECTOR_DEFINE_CHAN(gpt_counter_overflow_isr, GPT, COUNTER_OVERFLOW, 6);
#endif
#endif
static gpt_instance_ctrl_t g_timerC_ctrl;
static const timer_on_gpt_cfg_t g_timerC_extend =
{ .gtioca =
{ .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .gtiocb =
  { .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .shortest_pwm_signal = GPT_SHORTEST_LEVEL_OFF, };
static const timer_cfg_t g_timerC_cfg =
{ .mode = TIMER_MODE_PERIODIC, .period = 10, .unit = TIMER_UNIT_PERIOD_MSEC, .duty_cycle = 50, .duty_cycle_unit =
          TIMER_PWM_UNIT_RAW_COUNTS,
  .channel = 6, .autostart = false, .p_callback = gpt_MotorC_callback, .p_context = &g_timerC, .p_extend =
          &g_timerC_extend,
  .irq_ipl = (0), };
/* Instance structure to use this module. */
const timer_instance_t g_timerC =
{ .p_ctrl = &g_timerC_ctrl, .p_cfg = &g_timerC_cfg, .p_api = &g_timer_on_gpt };
#if (0) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_timerB) && !defined(SSP_SUPPRESS_ISR_GPT5)
SSP_VECTOR_DEFINE_CHAN(gpt_counter_overflow_isr, GPT, COUNTER_OVERFLOW, 5);
#endif
#endif
static gpt_instance_ctrl_t g_timerB_ctrl;
static const timer_on_gpt_cfg_t g_timerB_extend =
{ .gtioca =
{ .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .gtiocb =
  { .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .shortest_pwm_signal = GPT_SHORTEST_LEVEL_OFF, };
static const timer_cfg_t g_timerB_cfg =
{ .mode = TIMER_MODE_PERIODIC, .period = 10, .unit = TIMER_UNIT_PERIOD_MSEC, .duty_cycle = 50, .duty_cycle_unit =
          TIMER_PWM_UNIT_RAW_COUNTS,
  .channel = 5, .autostart = false, .p_callback = gpt_MotorB_callback, .p_context = &g_timerB, .p_extend =
          &g_timerB_extend,
  .irq_ipl = (0), };
/* Instance structure to use this module. */
const timer_instance_t g_timerB =
{ .p_ctrl = &g_timerB_ctrl, .p_cfg = &g_timerB_cfg, .p_api = &g_timer_on_gpt };
#if (0) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_timerA) && !defined(SSP_SUPPRESS_ISR_GPT2)
SSP_VECTOR_DEFINE_CHAN(gpt_counter_overflow_isr, GPT, COUNTER_OVERFLOW, 2);
#endif
#endif
static gpt_instance_ctrl_t g_timerA_ctrl;
static const timer_on_gpt_cfg_t g_timerA_extend =
{ .gtioca =
{ .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .gtiocb =
  { .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .shortest_pwm_signal = GPT_SHORTEST_LEVEL_OFF, };
static const timer_cfg_t g_timerA_cfg =
{ .mode = TIMER_MODE_PERIODIC, .period = 10, .unit = TIMER_UNIT_PERIOD_MSEC, .duty_cycle = 50, .duty_cycle_unit =
          TIMER_PWM_UNIT_RAW_COUNTS,
  .channel = 2, .autostart = false, .p_callback = gpt_MotorA_callback, .p_context = &g_timerA, .p_extend =
          &g_timerA_extend,
  .irq_ipl = (0), };
/* Instance structure to use this module. */
const timer_instance_t g_timerA =
{ .p_ctrl = &g_timerA_ctrl, .p_cfg = &g_timerA_cfg, .p_api = &g_timer_on_gpt };
#if (6) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_timer1) && !defined(SSP_SUPPRESS_ISR_GPT1)
SSP_VECTOR_DEFINE_CHAN(gpt_counter_overflow_isr, GPT, COUNTER_OVERFLOW, 1);
#endif
#endif
static gpt_instance_ctrl_t g_timer1_ctrl;
static const timer_on_gpt_cfg_t g_timer1_extend =
{ .gtioca =
{ .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .gtiocb =
  { .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .shortest_pwm_signal = GPT_SHORTEST_LEVEL_OFF, };
static const timer_cfg_t g_timer1_cfg =
{ .mode = TIMER_MODE_PERIODIC,
  .period = 10,
  .unit = TIMER_UNIT_PERIOD_MSEC,
  .duty_cycle = 50,
  .duty_cycle_unit = TIMER_PWM_UNIT_RAW_COUNTS,
  .channel = 1,
  .autostart = false,
  .p_callback = gpt_1_callback,
  .p_context = &g_timer1,
  .p_extend = &g_timer1_extend,
  .irq_ipl = (6), };
/* Instance structure to use this module. */
const timer_instance_t g_timer1 =
{ .p_ctrl = &g_timer1_ctrl, .p_cfg = &g_timer1_cfg, .p_api = &g_timer_on_gpt };
#if (0) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_timer0) && !defined(SSP_SUPPRESS_ISR_GPT0)
SSP_VECTOR_DEFINE_CHAN(gpt_counter_overflow_isr, GPT, COUNTER_OVERFLOW, 0);
#endif
#endif
static gpt_instance_ctrl_t g_timer0_ctrl;
static const timer_on_gpt_cfg_t g_timer0_extend =
{ .gtioca =
{ .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .gtiocb =
  { .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .shortest_pwm_signal = GPT_SHORTEST_LEVEL_OFF, };
static const timer_cfg_t g_timer0_cfg =
{ .mode = TIMER_MODE_PERIODIC,
  .period = 10,
  .unit = TIMER_UNIT_PERIOD_MSEC,
  .duty_cycle = 50,
  .duty_cycle_unit = TIMER_PWM_UNIT_RAW_COUNTS,
  .channel = 0,
  .autostart = false,
  .p_callback = gpt_0_callback,
  .p_context = &g_timer0,
  .p_extend = &g_timer0_extend,
  .irq_ipl = (0), };
/* Instance structure to use this module. */
const timer_instance_t g_timer0 =
{ .p_ctrl = &g_timer0_ctrl, .p_cfg = &g_timer0_cfg, .p_api = &g_timer_on_gpt };
#if (BSP_IRQ_DISABLED) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_adc1) && !defined(SSP_SUPPRESS_ISR_ADC1)
SSP_VECTOR_DEFINE_CHAN(adc_scan_end_isr, ADC, SCAN_END, 1);
#endif
#endif
#if (BSP_IRQ_DISABLED) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_adc1) && !defined(SSP_SUPPRESS_ISR_ADC1)
SSP_VECTOR_DEFINE_CHAN(adc_scan_end_b_isr, ADC, SCAN_END_B, 1);
#endif
#endif
adc_instance_ctrl_t g_adc1_ctrl;
const adc_cfg_t g_adc1_cfg =
{ .unit = 1,
  .mode = ADC_MODE_CONTINUOUS_SCAN,
  .resolution = ADC_RESOLUTION_12_BIT,
  .alignment = ADC_ALIGNMENT_RIGHT,
  .add_average_count = ADC_ADD_AVERAGE_FOUR,
  .clearing = ADC_CLEAR_AFTER_READ_ON,
  .trigger = ADC_TRIGGER_SOFTWARE,
  .trigger_group_b = ADC_TRIGGER_SYNC_ELC,
  .p_callback = NULL,
  .p_context = &g_adc1,
  .scan_end_ipl = (BSP_IRQ_DISABLED),
  .scan_end_b_ipl = (BSP_IRQ_DISABLED),
  .calib_adc_skip = false,
  .voltage_ref = ADC_EXTERNAL_VOLTAGE,
  .over_current = OVER_CURRENT_DETECTION_ENABLE,
  .pga0 = PGA_DISABLE,
  .pga1 = PGA_DISABLE,
  .pga2 = PGA_DISABLE, };
const adc_channel_cfg_t g_adc1_channel_cfg =
{ .scan_mask = (uint32_t) (
        ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) ADC_MASK_CHANNEL_2) | ((uint64_t) 0) | ((uint64_t) 0)
                | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
                | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
                | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
                | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
                | (0)),
  /** Group B channel mask is right shifted by 32 at the end to form the proper mask */
  .scan_mask_group_b = (uint32_t) (
          (((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) ADC_MASK_CHANNEL_2) | ((uint64_t) 0) | ((uint64_t) 0)
                  | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
                  | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
                  | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
                  | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
                  | (0)) >> 32),
  .priority_group_a = ADC_GROUP_A_PRIORITY_OFF, .add_mask = (uint32_t) (
          (0) | (0) | (ADC_MASK_CHANNEL_2) | (0) | (0) | (0) | (0) | (0) | (0) | (0) | (0) | (0) | (0) | (0) | (0) | (0)
                  | (0) | (0) | (0) | (0) | (0) | (0) | (0) | (0) | (0) | (0) | (0) | (0) | (0) | (0)),
  .sample_hold_mask = (uint32_t) ((0) | (0) | (0)), .sample_hold_states = 24, };
/* Instance structure to use this module. */
const adc_instance_t g_adc1 =
{ .p_ctrl = &g_adc1_ctrl, .p_cfg = &g_adc1_cfg, .p_channel_cfg = &g_adc1_channel_cfg, .p_api = &g_adc_on_adc };
#if (0) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_external_irqZ) && !defined(SSP_SUPPRESS_ISR_ICU2)
SSP_VECTOR_DEFINE(icu_irq_isr, ICU, IRQ2);
#endif
#endif
static icu_instance_ctrl_t g_external_irqZ_ctrl;
static const external_irq_cfg_t g_external_irqZ_cfg =
{ .channel = 2,
  .trigger = EXTERNAL_IRQ_TRIG_BOTH_EDGE,
  .filter_enable = true,
  .pclk_div = EXTERNAL_IRQ_PCLK_DIV_BY_64,
  .autostart = true,
  .p_callback = ext_irqZ_callback,
  .p_context = &g_external_irqZ,
  .p_extend = NULL,
  .irq_ipl = (0), };
/* Instance structure to use this module. */
const external_irq_instance_t g_external_irqZ =
{ .p_ctrl = &g_external_irqZ_ctrl, .p_cfg = &g_external_irqZ_cfg, .p_api = &g_external_irq_on_icu };
#if (0) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_external_irqY) && !defined(SSP_SUPPRESS_ISR_ICU7)
SSP_VECTOR_DEFINE(icu_irq_isr, ICU, IRQ7);
#endif
#endif
static icu_instance_ctrl_t g_external_irqY_ctrl;
static const external_irq_cfg_t g_external_irqY_cfg =
{ .channel = 7,
  .trigger = EXTERNAL_IRQ_TRIG_BOTH_EDGE,
  .filter_enable = true,
  .pclk_div = EXTERNAL_IRQ_PCLK_DIV_BY_64,
  .autostart = true,
  .p_callback = ext_irqY_callback,
  .p_context = &g_external_irqY,
  .p_extend = NULL,
  .irq_ipl = (0), };
/* Instance structure to use this module. */
const external_irq_instance_t g_external_irqY =
{ .p_ctrl = &g_external_irqY_ctrl, .p_cfg = &g_external_irqY_cfg, .p_api = &g_external_irq_on_icu };
#if (0) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_external_irqX) && !defined(SSP_SUPPRESS_ISR_ICU3)
SSP_VECTOR_DEFINE(icu_irq_isr, ICU, IRQ3);
#endif
#endif
static icu_instance_ctrl_t g_external_irqX_ctrl;
static const external_irq_cfg_t g_external_irqX_cfg =
{ .channel = 3,
  .trigger = EXTERNAL_IRQ_TRIG_BOTH_EDGE,
  .filter_enable = true,
  .pclk_div = EXTERNAL_IRQ_PCLK_DIV_BY_64,
  .autostart = true,
  .p_callback = ext_irqX_callback,
  .p_context = &g_external_irqX,
  .p_extend = NULL,
  .irq_ipl = (0), };
/* Instance structure to use this module. */
const external_irq_instance_t g_external_irqX =
{ .p_ctrl = &g_external_irqX_ctrl, .p_cfg = &g_external_irqX_cfg, .p_api = &g_external_irq_on_icu };
#if (0) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_timer_gpt_4) && !defined(SSP_SUPPRESS_ISR_GPT4)
SSP_VECTOR_DEFINE_CHAN(gpt_counter_overflow_isr, GPT, COUNTER_OVERFLOW, 4);
#endif
#endif
static gpt_instance_ctrl_t g_timer_gpt_4_ctrl;
static const timer_on_gpt_cfg_t g_timer_gpt_4_extend =
{ .gtioca =
{ .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .gtiocb =
  { .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .shortest_pwm_signal = GPT_SHORTEST_LEVEL_OFF, };
static const timer_cfg_t g_timer_gpt_4_cfg =
{ .mode = TIMER_MODE_PERIODIC, .period = 10, .unit = TIMER_UNIT_PERIOD_MSEC, .duty_cycle = 50, .duty_cycle_unit =
          TIMER_PWM_UNIT_RAW_COUNTS,
  .channel = 4, .autostart = false, .p_callback = gpt_4_callback, .p_context = &g_timer_gpt_4, .p_extend =
          &g_timer_gpt_4_extend,
  .irq_ipl = (0), };
/* Instance structure to use this module. */
const timer_instance_t g_timer_gpt_4 =
{ .p_ctrl = &g_timer_gpt_4_ctrl, .p_cfg = &g_timer_gpt_4_cfg, .p_api = &g_timer_on_gpt };
#if (0) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_timer_gpt_7) && !defined(SSP_SUPPRESS_ISR_GPT7)
SSP_VECTOR_DEFINE_CHAN(gpt_counter_overflow_isr, GPT, COUNTER_OVERFLOW, 7);
#endif
#endif
static gpt_instance_ctrl_t g_timer_gpt_7_ctrl;
static const timer_on_gpt_cfg_t g_timer_gpt_7_extend =
{ .gtioca =
{ .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .gtiocb =
  { .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .shortest_pwm_signal = GPT_SHORTEST_LEVEL_OFF, };
static const timer_cfg_t g_timer_gpt_7_cfg =
{ .mode = TIMER_MODE_PERIODIC, .period = 10, .unit = TIMER_UNIT_PERIOD_MSEC, .duty_cycle = 50, .duty_cycle_unit =
          TIMER_PWM_UNIT_RAW_COUNTS,
  .channel = 7, .autostart = false, .p_callback = gpt_7_callback, .p_context = &g_timer_gpt_7, .p_extend =
          &g_timer_gpt_7_extend,
  .irq_ipl = (0), };
/* Instance structure to use this module. */
const timer_instance_t g_timer_gpt_7 =
{ .p_ctrl = &g_timer_gpt_7_ctrl, .p_cfg = &g_timer_gpt_7_cfg, .p_api = &g_timer_on_gpt };
#if (0) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_timer_gpt_3) && !defined(SSP_SUPPRESS_ISR_GPT3)
SSP_VECTOR_DEFINE_CHAN(gpt_counter_overflow_isr, GPT, COUNTER_OVERFLOW, 3);
#endif
#endif
static gpt_instance_ctrl_t g_timer_gpt_3_ctrl;
static const timer_on_gpt_cfg_t g_timer_gpt_3_extend =
{ .gtioca =
{ .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .gtiocb =
  { .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .shortest_pwm_signal = GPT_SHORTEST_LEVEL_OFF, };
static const timer_cfg_t g_timer_gpt_3_cfg =
{ .mode = TIMER_MODE_PERIODIC, .period = 10, .unit = TIMER_UNIT_PERIOD_MSEC, .duty_cycle = 50, .duty_cycle_unit =
          TIMER_PWM_UNIT_RAW_COUNTS,
  .channel = 3, .autostart = false, .p_callback = gpt_3_callback, .p_context = &g_timer_gpt_3, .p_extend =
          &g_timer_gpt_3_extend,
  .irq_ipl = (0), };
/* Instance structure to use this module. */
const timer_instance_t g_timer_gpt_3 =
{ .p_ctrl = &g_timer_gpt_3_ctrl, .p_cfg = &g_timer_gpt_3_cfg, .p_api = &g_timer_on_gpt };
void g_hal_init(void)
{
    g_common_init ();
}
