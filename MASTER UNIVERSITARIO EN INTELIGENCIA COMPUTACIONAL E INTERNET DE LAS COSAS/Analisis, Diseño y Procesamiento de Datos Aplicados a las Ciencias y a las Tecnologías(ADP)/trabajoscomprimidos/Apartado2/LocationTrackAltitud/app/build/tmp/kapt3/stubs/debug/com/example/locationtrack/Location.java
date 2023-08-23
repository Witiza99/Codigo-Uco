package com.example.locationtrack;

import java.lang.System;

@kotlin.Metadata(mv = {1, 6, 0}, k = 1, d1 = {"\u0000,\n\u0002\u0018\u0002\n\u0002\u0018\u0002\n\u0000\n\u0002\u0018\u0002\n\u0000\n\u0002\u0010\u000e\n\u0000\n\u0002\u0010\u0007\n\u0000\n\u0002\u0010\u0006\n\u0002\b\u0003\n\u0002\u0010\t\n\u0002\b\u001d\b\u0016\u0018\u00002\u00020\u0001BW\u0012\n\b\u0002\u0010\u0002\u001a\u0004\u0018\u00010\u0003\u0012\b\b\u0002\u0010\u0004\u001a\u00020\u0005\u0012\b\b\u0002\u0010\u0006\u001a\u00020\u0007\u0012\b\b\u0002\u0010\b\u001a\u00020\t\u0012\b\b\u0002\u0010\n\u001a\u00020\t\u0012\b\b\u0002\u0010\u000b\u001a\u00020\u0007\u0012\b\b\u0002\u0010\f\u001a\u00020\r\u0012\b\b\u0002\u0010\u000e\u001a\u00020\t\u00a2\u0006\u0002\u0010\u000fR \u0010\u0002\u001a\u0004\u0018\u00010\u00038\u0006@\u0006X\u0087\u000e\u00a2\u0006\u000e\n\u0000\u001a\u0004\b\u0010\u0010\u0011\"\u0004\b\u0012\u0010\u0013R\u001a\u0010\u0004\u001a\u00020\u0005X\u0086\u000e\u00a2\u0006\u000e\n\u0000\u001a\u0004\b\u0014\u0010\u0015\"\u0004\b\u0016\u0010\u0017R\u001a\u0010\u0006\u001a\u00020\u0007X\u0086\u000e\u00a2\u0006\u000e\n\u0000\u001a\u0004\b\u0018\u0010\u0019\"\u0004\b\u001a\u0010\u001bR\u001a\u0010\u000e\u001a\u00020\tX\u0086\u000e\u00a2\u0006\u000e\n\u0000\u001a\u0004\b\u001c\u0010\u001d\"\u0004\b\u001e\u0010\u001fR\u001a\u0010\b\u001a\u00020\tX\u0086\u000e\u00a2\u0006\u000e\n\u0000\u001a\u0004\b \u0010\u001d\"\u0004\b!\u0010\u001fR\u001a\u0010\n\u001a\u00020\tX\u0086\u000e\u00a2\u0006\u000e\n\u0000\u001a\u0004\b\"\u0010\u001d\"\u0004\b#\u0010\u001fR\u001a\u0010\u000b\u001a\u00020\u0007X\u0086\u000e\u00a2\u0006\u000e\n\u0000\u001a\u0004\b$\u0010\u0019\"\u0004\b%\u0010\u001bR\u001a\u0010\f\u001a\u00020\rX\u0086\u000e\u00a2\u0006\u000e\n\u0000\u001a\u0004\b&\u0010\'\"\u0004\b(\u0010)\u00a8\u0006*"}, d2 = {"Lcom/example/locationtrack/Location;", "Lio/realm/RealmObject;", "_id", "Lorg/bson/types/ObjectId;", "_partition", "", "accuracy", "", "latitude", "", "longitude", "speed", "time", "", "altitude", "(Lorg/bson/types/ObjectId;Ljava/lang/String;FDDFJD)V", "get_id", "()Lorg/bson/types/ObjectId;", "set_id", "(Lorg/bson/types/ObjectId;)V", "get_partition", "()Ljava/lang/String;", "set_partition", "(Ljava/lang/String;)V", "getAccuracy", "()F", "setAccuracy", "(F)V", "getAltitude", "()D", "setAltitude", "(D)V", "getLatitude", "setLatitude", "getLongitude", "setLongitude", "getSpeed", "setSpeed", "getTime", "()J", "setTime", "(J)V", "app_debug"})
public class Location extends io.realm.RealmObject {
    @org.jetbrains.annotations.Nullable()
    @io.realm.annotations.PrimaryKey()
    private org.bson.types.ObjectId _id;
    @org.jetbrains.annotations.NotNull()
    private java.lang.String _partition;
    private float accuracy;
    private double latitude;
    private double longitude;
    private float speed;
    private long time;
    private double altitude;
    
    public Location() {
        super();
    }
    
    public Location(@org.jetbrains.annotations.Nullable()
    org.bson.types.ObjectId _id, @org.jetbrains.annotations.NotNull()
    java.lang.String _partition, float accuracy, double latitude, double longitude, float speed, long time, double altitude) {
        super();
    }
    
    @org.jetbrains.annotations.Nullable()
    public final org.bson.types.ObjectId get_id() {
        return null;
    }
    
    public final void set_id(@org.jetbrains.annotations.Nullable()
    org.bson.types.ObjectId p0) {
    }
    
    @org.jetbrains.annotations.NotNull()
    public final java.lang.String get_partition() {
        return null;
    }
    
    public final void set_partition(@org.jetbrains.annotations.NotNull()
    java.lang.String p0) {
    }
    
    public final float getAccuracy() {
        return 0.0F;
    }
    
    public final void setAccuracy(float p0) {
    }
    
    public final double getLatitude() {
        return 0.0;
    }
    
    public final void setLatitude(double p0) {
    }
    
    public final double getLongitude() {
        return 0.0;
    }
    
    public final void setLongitude(double p0) {
    }
    
    public final float getSpeed() {
        return 0.0F;
    }
    
    public final void setSpeed(float p0) {
    }
    
    public final long getTime() {
        return 0L;
    }
    
    public final void setTime(long p0) {
    }
    
    public final double getAltitude() {
        return 0.0;
    }
    
    public final void setAltitude(double p0) {
    }
}