#pragma once
#define FILE_NOT_CHOSEN_TEXT "File not chosen."
#define FILE_CHOSEN_TEXT "File chosen."
#define ON_PROCESS_TEXT "On process."
#define PROCESSED_TEXT "Processed."


enum class FILE_PROCESSING_STATUS
{
    UNDEFINED,
    FILE_NOT_CHOSEN,
    FILE_CHOSEN,
    ON_PROCESS,
    PROCESSED
};