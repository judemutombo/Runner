


float normalize(float min, float max, float low, float high, float value){

    if( high == low)
        throw ("Low and High values cannot be the same.");

    return min + ((value - low) / (high - low)) * (max - min);
    
}