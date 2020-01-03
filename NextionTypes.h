/*! \file */

#pragma once

/*!
 * \enum NextionValue
 * \brief Values used in messages.
 */
enum NextionValue
{
  NEX_RET_STARTUP = 0x00,
  NEX_RET_CMD_FAILED = 0x00,
  NEX_RET_CMD_FINISHED = 0x01,

  NEX_RET_INVALID_COMPONENT_ID = 0x02,
  NEX_RET_INVALID_PAGE_ID = 0x03,
  NEX_RET_INVALID_PICTURE_ID = 0x04,
  NEX_RET_INVALID_FONT_ID = 0x05,
  NEX_RET_INVALID_FILE_OP = 0x06,
  NEX_RET_INVALID_CRC = 0x09,
  NEX_RET_INVALID_BAUD = 0x11,
  NEX_RET_INVALID_WAVEFORM_ID_CHANNEL = 0x12,
  NEX_RET_INVALID_VARIABLE = 0x1A,
  NEX_RET_INVALID_OPERATION = 0x1B,
  NEX_RET_FAILED_TO_ASSIGN = 0x1C,
  NEX_RET_EEPROM_OP_FAILED = 0x1D,
  NEX_RET_INVALID_NUM_PARAMS = 0x1E,
  NEX_RET_IO_OP_FAILED = 0x1F,
  NEX_RET_INVALID_ESCAPE_CHAR = 0x20,
  NEX_RET_VAR_NAME_TOO_LONG = 0x23,
  NEX_RET_SERIAL_BUFFER_OVERFLOW = 0x24,

  NEX_RET_EVENT_TOUCH_HEAD = 0x65,

  NEX_RET_CURRENT_PAGE_ID_HEAD = 0x66,

  NEX_RET_EVENT_POSITION_HEAD = 0x67,
  NEX_RET_EVENT_SLEEP_POSITION_HEAD = 0x68,

  NEX_RET_STRING_HEAD = 0x70,
  NEX_RET_NUMBER_HEAD = 0x71,

  NEX_RET_EVENT_AUTO_SLEEP = 0x86,
  NEX_RET_EVENT_AUTO_WAKE_UP = 0x87,
  NEX_RET_EVENT_LAUNCHED = 0x88,
  NEX_RET_EVENT_UPGRADED = 0x89,
  NEX_RET_EVENT_TRANSPARENT_DATA_FINISHED = 0xFD,
  NEX_RET_EVENT_TRANSPARENT_DATA_READY = 0xFE
};

/*!
 * \enum NextionFontAlignment
 * \brief Font alignment modes.
 */
enum NextionFontAlignment
{
  NEX_FA_NONE = -1,     //!< Undefined
  NEX_FA_LEFT_UP = 0,   //!< Left (x) or top (y)
  NEX_FA_CENTRE = 1,    //!< Centre
  NEX_FA_RIGHT_DOWN = 2 //!< Right (x) or bottom (y)
};

/*!
 * \enum NextionBackground
 * \brief Background modes for widgets/drawables with backgrounds.
 */
enum NextionBackground
{
  NEX_BG_NONE = -1,       //!< Undefined
  NEX_BG_CROPIMAGE = 0,   //!< Cropped image
  NEX_BG_SOLIDCOLOUR = 1, //!< Solid colour
  NEW_BG_IMAGE = 2        //!< Full size image
};

/*!
 * \enum NextionColour
 * \brief Several default colour values.
 */
enum NextionColour
{
  NEX_COL_NONE = -1,
  NEX_COL_BLACK = 0,
  NEX_COL_WHITE = 65535,
  NEX_COL_RED = 63488,
  NEX_COL_GREEN = 2016,
  NEX_COL_BLUE = 31,
  NEX_COL_GRAY = 33840,
  NEX_COL_BROWN = 48192,
  NEX_COL_YELLOW = 65504
};

/*!
 * \enum NextionEventType
 * \brief Type of events received from device.
 */
enum NextionEventType
{
  NEX_EVENT_PUSH = (0x01),
  NEX_EVENT_POP = (0x00),
  NEX_EVENT_BOTH
};

/*!
 * \enum NextionScrollDirection
 * \brief Directions for scolling.
 */
enum NextionScrollDirection
{
  NEX_SCROLL_NONE = -1,
  NEX_SCROLL_LEFT = 1,
  NEX_SCROLL_RIGHT = 0,
  NEX_SCROLL_UP = 3,
  NEX_SCROLL_DOWN = 2
};
