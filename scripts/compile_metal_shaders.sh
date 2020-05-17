xcrun -sdk macosx metal -c resources/shaders/MSL/Simple.metal -o resources/shaders/MSL/KevShaderLib.air && \
rm -f resources/shaders/MSL/KevShaderLib.metallib &&\
xcrun -sdk macosx metallib resources/shaders/MSL/KevShaderLib.air -o resources/shaders/MSL/KevShaderLib.metallib 
rm -f resources/shaders/MSL/KevShaderLib.air