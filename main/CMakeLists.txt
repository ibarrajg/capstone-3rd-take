idf_component_register(
    SRCS 
        "main.c"
        "lora_receive.cpp" 
        "lora_transmit.cpp" 
        "message.cpp" 
        "message_frame.cpp"
    INCLUDE_DIRS "."
    )