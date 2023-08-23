package io.realm;


import android.annotation.TargetApi;
import android.os.Build;
import android.util.JsonReader;
import android.util.JsonToken;
import io.realm.ImportFlag;
import io.realm.ProxyUtils;
import io.realm.exceptions.RealmMigrationNeededException;
import io.realm.internal.ColumnInfo;
import io.realm.internal.NativeContext;
import io.realm.internal.OsList;
import io.realm.internal.OsMap;
import io.realm.internal.OsObject;
import io.realm.internal.OsObjectSchemaInfo;
import io.realm.internal.OsSchemaInfo;
import io.realm.internal.OsSet;
import io.realm.internal.Property;
import io.realm.internal.RealmObjectProxy;
import io.realm.internal.Row;
import io.realm.internal.Table;
import io.realm.internal.android.JsonUtils;
import io.realm.internal.core.NativeRealmAny;
import io.realm.internal.objectstore.OsObjectBuilder;
import io.realm.log.RealmLog;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Date;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

@SuppressWarnings("all")
public class com_example_locationtrack_LocationRealmProxy extends com.example.locationtrack.Location
    implements RealmObjectProxy, com_example_locationtrack_LocationRealmProxyInterface {

    static final class LocationColumnInfo extends ColumnInfo {
        long _idColKey;
        long _partitionColKey;
        long accuracyColKey;
        long latitudeColKey;
        long longitudeColKey;
        long speedColKey;
        long timeColKey;
        long altitudeColKey;

        LocationColumnInfo(OsSchemaInfo schemaInfo) {
            super(8);
            OsObjectSchemaInfo objectSchemaInfo = schemaInfo.getObjectSchemaInfo("Location");
            this._idColKey = addColumnDetails("_id", "_id", objectSchemaInfo);
            this._partitionColKey = addColumnDetails("_partition", "_partition", objectSchemaInfo);
            this.accuracyColKey = addColumnDetails("accuracy", "accuracy", objectSchemaInfo);
            this.latitudeColKey = addColumnDetails("latitude", "latitude", objectSchemaInfo);
            this.longitudeColKey = addColumnDetails("longitude", "longitude", objectSchemaInfo);
            this.speedColKey = addColumnDetails("speed", "speed", objectSchemaInfo);
            this.timeColKey = addColumnDetails("time", "time", objectSchemaInfo);
            this.altitudeColKey = addColumnDetails("altitude", "altitude", objectSchemaInfo);
        }

        LocationColumnInfo(ColumnInfo src, boolean mutable) {
            super(src, mutable);
            copy(src, this);
        }

        @Override
        protected final ColumnInfo copy(boolean mutable) {
            return new LocationColumnInfo(this, mutable);
        }

        @Override
        protected final void copy(ColumnInfo rawSrc, ColumnInfo rawDst) {
            final LocationColumnInfo src = (LocationColumnInfo) rawSrc;
            final LocationColumnInfo dst = (LocationColumnInfo) rawDst;
            dst._idColKey = src._idColKey;
            dst._partitionColKey = src._partitionColKey;
            dst.accuracyColKey = src.accuracyColKey;
            dst.latitudeColKey = src.latitudeColKey;
            dst.longitudeColKey = src.longitudeColKey;
            dst.speedColKey = src.speedColKey;
            dst.timeColKey = src.timeColKey;
            dst.altitudeColKey = src.altitudeColKey;
        }
    }

    private static final String NO_ALIAS = "";
    private static final OsObjectSchemaInfo expectedObjectSchemaInfo = createExpectedObjectSchemaInfo();

    private LocationColumnInfo columnInfo;
    private ProxyState<com.example.locationtrack.Location> proxyState;

    com_example_locationtrack_LocationRealmProxy() {
        proxyState.setConstructionFinished();
    }

    @Override
    public void realm$injectObjectContext() {
        if (this.proxyState != null) {
            return;
        }
        final BaseRealm.RealmObjectContext context = BaseRealm.objectContext.get();
        this.columnInfo = (LocationColumnInfo) context.getColumnInfo();
        this.proxyState = new ProxyState<com.example.locationtrack.Location>(this);
        proxyState.setRealm$realm(context.getRealm());
        proxyState.setRow$realm(context.getRow());
        proxyState.setAcceptDefaultValue$realm(context.getAcceptDefaultValue());
        proxyState.setExcludeFields$realm(context.getExcludeFields());
    }

    @Override
    @SuppressWarnings("cast")
    public org.bson.types.ObjectId realmGet$_id() {
        proxyState.getRealm$realm().checkIfValid();
        if (proxyState.getRow$realm().isNull(columnInfo._idColKey)) {
            return null;
        }
        return (org.bson.types.ObjectId) proxyState.getRow$realm().getObjectId(columnInfo._idColKey);
    }

    @Override
    public void realmSet$_id(org.bson.types.ObjectId value) {
        if (proxyState.isUnderConstruction()) {
            // default value of the primary key is always ignored.
            return;
        }

        proxyState.getRealm$realm().checkIfValid();
        throw new io.realm.exceptions.RealmException("Primary key field '_id' cannot be changed after object was created.");
    }

    @Override
    @SuppressWarnings("cast")
    public String realmGet$_partition() {
        proxyState.getRealm$realm().checkIfValid();
        return (java.lang.String) proxyState.getRow$realm().getString(columnInfo._partitionColKey);
    }

    @Override
    public void realmSet$_partition(String value) {
        if (proxyState.isUnderConstruction()) {
            if (!proxyState.getAcceptDefaultValue$realm()) {
                return;
            }
            final Row row = proxyState.getRow$realm();
            if (value == null) {
                throw new IllegalArgumentException("Trying to set non-nullable field '_partition' to null.");
            }
            row.getTable().setString(columnInfo._partitionColKey, row.getObjectKey(), value, true);
            return;
        }

        proxyState.getRealm$realm().checkIfValid();
        if (value == null) {
            throw new IllegalArgumentException("Trying to set non-nullable field '_partition' to null.");
        }
        proxyState.getRow$realm().setString(columnInfo._partitionColKey, value);
    }

    @Override
    @SuppressWarnings("cast")
    public float realmGet$accuracy() {
        proxyState.getRealm$realm().checkIfValid();
        return (float) proxyState.getRow$realm().getFloat(columnInfo.accuracyColKey);
    }

    @Override
    public void realmSet$accuracy(float value) {
        if (proxyState.isUnderConstruction()) {
            if (!proxyState.getAcceptDefaultValue$realm()) {
                return;
            }
            final Row row = proxyState.getRow$realm();
            row.getTable().setFloat(columnInfo.accuracyColKey, row.getObjectKey(), value, true);
            return;
        }

        proxyState.getRealm$realm().checkIfValid();
        proxyState.getRow$realm().setFloat(columnInfo.accuracyColKey, value);
    }

    @Override
    @SuppressWarnings("cast")
    public double realmGet$latitude() {
        proxyState.getRealm$realm().checkIfValid();
        return (double) proxyState.getRow$realm().getDouble(columnInfo.latitudeColKey);
    }

    @Override
    public void realmSet$latitude(double value) {
        if (proxyState.isUnderConstruction()) {
            if (!proxyState.getAcceptDefaultValue$realm()) {
                return;
            }
            final Row row = proxyState.getRow$realm();
            row.getTable().setDouble(columnInfo.latitudeColKey, row.getObjectKey(), value, true);
            return;
        }

        proxyState.getRealm$realm().checkIfValid();
        proxyState.getRow$realm().setDouble(columnInfo.latitudeColKey, value);
    }

    @Override
    @SuppressWarnings("cast")
    public double realmGet$longitude() {
        proxyState.getRealm$realm().checkIfValid();
        return (double) proxyState.getRow$realm().getDouble(columnInfo.longitudeColKey);
    }

    @Override
    public void realmSet$longitude(double value) {
        if (proxyState.isUnderConstruction()) {
            if (!proxyState.getAcceptDefaultValue$realm()) {
                return;
            }
            final Row row = proxyState.getRow$realm();
            row.getTable().setDouble(columnInfo.longitudeColKey, row.getObjectKey(), value, true);
            return;
        }

        proxyState.getRealm$realm().checkIfValid();
        proxyState.getRow$realm().setDouble(columnInfo.longitudeColKey, value);
    }

    @Override
    @SuppressWarnings("cast")
    public float realmGet$speed() {
        proxyState.getRealm$realm().checkIfValid();
        return (float) proxyState.getRow$realm().getFloat(columnInfo.speedColKey);
    }

    @Override
    public void realmSet$speed(float value) {
        if (proxyState.isUnderConstruction()) {
            if (!proxyState.getAcceptDefaultValue$realm()) {
                return;
            }
            final Row row = proxyState.getRow$realm();
            row.getTable().setFloat(columnInfo.speedColKey, row.getObjectKey(), value, true);
            return;
        }

        proxyState.getRealm$realm().checkIfValid();
        proxyState.getRow$realm().setFloat(columnInfo.speedColKey, value);
    }

    @Override
    @SuppressWarnings("cast")
    public long realmGet$time() {
        proxyState.getRealm$realm().checkIfValid();
        return (long) proxyState.getRow$realm().getLong(columnInfo.timeColKey);
    }

    @Override
    public void realmSet$time(long value) {
        if (proxyState.isUnderConstruction()) {
            if (!proxyState.getAcceptDefaultValue$realm()) {
                return;
            }
            final Row row = proxyState.getRow$realm();
            row.getTable().setLong(columnInfo.timeColKey, row.getObjectKey(), value, true);
            return;
        }

        proxyState.getRealm$realm().checkIfValid();
        proxyState.getRow$realm().setLong(columnInfo.timeColKey, value);
    }

    @Override
    @SuppressWarnings("cast")
    public double realmGet$altitude() {
        proxyState.getRealm$realm().checkIfValid();
        return (double) proxyState.getRow$realm().getDouble(columnInfo.altitudeColKey);
    }

    @Override
    public void realmSet$altitude(double value) {
        if (proxyState.isUnderConstruction()) {
            if (!proxyState.getAcceptDefaultValue$realm()) {
                return;
            }
            final Row row = proxyState.getRow$realm();
            row.getTable().setDouble(columnInfo.altitudeColKey, row.getObjectKey(), value, true);
            return;
        }

        proxyState.getRealm$realm().checkIfValid();
        proxyState.getRow$realm().setDouble(columnInfo.altitudeColKey, value);
    }

    private static OsObjectSchemaInfo createExpectedObjectSchemaInfo() {
        OsObjectSchemaInfo.Builder builder = new OsObjectSchemaInfo.Builder(NO_ALIAS, "Location", false, 8, 0);
        builder.addPersistedProperty(NO_ALIAS, "_id", RealmFieldType.OBJECT_ID, Property.PRIMARY_KEY, !Property.INDEXED, !Property.REQUIRED);
        builder.addPersistedProperty(NO_ALIAS, "_partition", RealmFieldType.STRING, !Property.PRIMARY_KEY, !Property.INDEXED, Property.REQUIRED);
        builder.addPersistedProperty(NO_ALIAS, "accuracy", RealmFieldType.FLOAT, !Property.PRIMARY_KEY, !Property.INDEXED, Property.REQUIRED);
        builder.addPersistedProperty(NO_ALIAS, "latitude", RealmFieldType.DOUBLE, !Property.PRIMARY_KEY, !Property.INDEXED, Property.REQUIRED);
        builder.addPersistedProperty(NO_ALIAS, "longitude", RealmFieldType.DOUBLE, !Property.PRIMARY_KEY, !Property.INDEXED, Property.REQUIRED);
        builder.addPersistedProperty(NO_ALIAS, "speed", RealmFieldType.FLOAT, !Property.PRIMARY_KEY, !Property.INDEXED, Property.REQUIRED);
        builder.addPersistedProperty(NO_ALIAS, "time", RealmFieldType.INTEGER, !Property.PRIMARY_KEY, !Property.INDEXED, Property.REQUIRED);
        builder.addPersistedProperty(NO_ALIAS, "altitude", RealmFieldType.DOUBLE, !Property.PRIMARY_KEY, !Property.INDEXED, Property.REQUIRED);
        return builder.build();
    }

    public static OsObjectSchemaInfo getExpectedObjectSchemaInfo() {
        return expectedObjectSchemaInfo;
    }

    public static LocationColumnInfo createColumnInfo(OsSchemaInfo schemaInfo) {
        return new LocationColumnInfo(schemaInfo);
    }

    public static String getSimpleClassName() {
        return "Location";
    }

    public static final class ClassNameHelper {
        public static final String INTERNAL_CLASS_NAME = "Location";
    }

    @SuppressWarnings("cast")
    public static com.example.locationtrack.Location createOrUpdateUsingJsonObject(Realm realm, JSONObject json, boolean update)
        throws JSONException {
        final List<String> excludeFields = Collections.<String> emptyList();
        com.example.locationtrack.Location obj = null;
        if (update) {
            Table table = realm.getTable(com.example.locationtrack.Location.class);
            LocationColumnInfo columnInfo = (LocationColumnInfo) realm.getSchema().getColumnInfo(com.example.locationtrack.Location.class);
            long pkColumnKey = columnInfo._idColKey;
            long objKey = Table.NO_MATCH;
            if (json.isNull("_id")) {
                objKey = table.findFirstNull(pkColumnKey);
            } else {
                objKey = table.findFirstObjectId(pkColumnKey, new org.bson.types.ObjectId((String)json.get("_id")));
            }
            if (objKey != Table.NO_MATCH) {
                final BaseRealm.RealmObjectContext objectContext = BaseRealm.objectContext.get();
                try {
                    objectContext.set(realm, table.getUncheckedRow(objKey), realm.getSchema().getColumnInfo(com.example.locationtrack.Location.class), false, Collections.<String> emptyList());
                    obj = new io.realm.com_example_locationtrack_LocationRealmProxy();
                } finally {
                    objectContext.clear();
                }
            }
        }
        if (obj == null) {
            if (json.has("_id")) {
                if (json.isNull("_id")) {
                    obj = (io.realm.com_example_locationtrack_LocationRealmProxy) realm.createObjectInternal(com.example.locationtrack.Location.class, null, true, excludeFields);
                } else {
                    obj = (io.realm.com_example_locationtrack_LocationRealmProxy) realm.createObjectInternal(com.example.locationtrack.Location.class, json.get("_id"), true, excludeFields);
                }
            } else {
                throw new IllegalArgumentException("JSON object doesn't have the primary key field '_id'.");
            }
        }

        final com_example_locationtrack_LocationRealmProxyInterface objProxy = (com_example_locationtrack_LocationRealmProxyInterface) obj;
        if (json.has("_partition")) {
            if (json.isNull("_partition")) {
                objProxy.realmSet$_partition(null);
            } else {
                objProxy.realmSet$_partition((String) json.getString("_partition"));
            }
        }
        if (json.has("accuracy")) {
            if (json.isNull("accuracy")) {
                throw new IllegalArgumentException("Trying to set non-nullable field 'accuracy' to null.");
            } else {
                objProxy.realmSet$accuracy((float) json.getDouble("accuracy"));
            }
        }
        if (json.has("latitude")) {
            if (json.isNull("latitude")) {
                throw new IllegalArgumentException("Trying to set non-nullable field 'latitude' to null.");
            } else {
                objProxy.realmSet$latitude((double) json.getDouble("latitude"));
            }
        }
        if (json.has("longitude")) {
            if (json.isNull("longitude")) {
                throw new IllegalArgumentException("Trying to set non-nullable field 'longitude' to null.");
            } else {
                objProxy.realmSet$longitude((double) json.getDouble("longitude"));
            }
        }
        if (json.has("speed")) {
            if (json.isNull("speed")) {
                throw new IllegalArgumentException("Trying to set non-nullable field 'speed' to null.");
            } else {
                objProxy.realmSet$speed((float) json.getDouble("speed"));
            }
        }
        if (json.has("time")) {
            if (json.isNull("time")) {
                throw new IllegalArgumentException("Trying to set non-nullable field 'time' to null.");
            } else {
                objProxy.realmSet$time((long) json.getLong("time"));
            }
        }
        if (json.has("altitude")) {
            if (json.isNull("altitude")) {
                throw new IllegalArgumentException("Trying to set non-nullable field 'altitude' to null.");
            } else {
                objProxy.realmSet$altitude((double) json.getDouble("altitude"));
            }
        }
        return obj;
    }

    @SuppressWarnings("cast")
    @TargetApi(Build.VERSION_CODES.HONEYCOMB)
    public static com.example.locationtrack.Location createUsingJsonStream(Realm realm, JsonReader reader)
        throws IOException {
        boolean jsonHasPrimaryKey = false;
        final com.example.locationtrack.Location obj = new com.example.locationtrack.Location();
        final com_example_locationtrack_LocationRealmProxyInterface objProxy = (com_example_locationtrack_LocationRealmProxyInterface) obj;
        reader.beginObject();
        while (reader.hasNext()) {
            String name = reader.nextName();
            if (false) {
            } else if (name.equals("_id")) {
                if (reader.peek() == JsonToken.NULL) {
                    reader.skipValue();
                    objProxy.realmSet$_id(null);
                } else {
                    objProxy.realmSet$_id(new org.bson.types.ObjectId(reader.nextString()));
                }
            } else if (name.equals("_partition")) {
                if (reader.peek() != JsonToken.NULL) {
                    objProxy.realmSet$_partition((String) reader.nextString());
                } else {
                    reader.skipValue();
                    objProxy.realmSet$_partition(null);
                }
            } else if (name.equals("accuracy")) {
                if (reader.peek() != JsonToken.NULL) {
                    objProxy.realmSet$accuracy((float) reader.nextDouble());
                } else {
                    reader.skipValue();
                    throw new IllegalArgumentException("Trying to set non-nullable field 'accuracy' to null.");
                }
            } else if (name.equals("latitude")) {
                if (reader.peek() != JsonToken.NULL) {
                    objProxy.realmSet$latitude((double) reader.nextDouble());
                } else {
                    reader.skipValue();
                    throw new IllegalArgumentException("Trying to set non-nullable field 'latitude' to null.");
                }
            } else if (name.equals("longitude")) {
                if (reader.peek() != JsonToken.NULL) {
                    objProxy.realmSet$longitude((double) reader.nextDouble());
                } else {
                    reader.skipValue();
                    throw new IllegalArgumentException("Trying to set non-nullable field 'longitude' to null.");
                }
            } else if (name.equals("speed")) {
                if (reader.peek() != JsonToken.NULL) {
                    objProxy.realmSet$speed((float) reader.nextDouble());
                } else {
                    reader.skipValue();
                    throw new IllegalArgumentException("Trying to set non-nullable field 'speed' to null.");
                }
            } else if (name.equals("time")) {
                if (reader.peek() != JsonToken.NULL) {
                    objProxy.realmSet$time((long) reader.nextLong());
                } else {
                    reader.skipValue();
                    throw new IllegalArgumentException("Trying to set non-nullable field 'time' to null.");
                }
            } else if (name.equals("altitude")) {
                if (reader.peek() != JsonToken.NULL) {
                    objProxy.realmSet$altitude((double) reader.nextDouble());
                } else {
                    reader.skipValue();
                    throw new IllegalArgumentException("Trying to set non-nullable field 'altitude' to null.");
                }
            } else {
                reader.skipValue();
            }
        }
        reader.endObject();
        if (!jsonHasPrimaryKey) {
            throw new IllegalArgumentException("JSON object doesn't have the primary key field '_id'.");
        }
        return realm.copyToRealmOrUpdate(obj);
    }

    static com_example_locationtrack_LocationRealmProxy newProxyInstance(BaseRealm realm, Row row) {
        // Ignore default values to avoid creating unexpected objects from RealmModel/RealmList fields
        final BaseRealm.RealmObjectContext objectContext = BaseRealm.objectContext.get();
        objectContext.set(realm, row, realm.getSchema().getColumnInfo(com.example.locationtrack.Location.class), false, Collections.<String>emptyList());
        io.realm.com_example_locationtrack_LocationRealmProxy obj = new io.realm.com_example_locationtrack_LocationRealmProxy();
        objectContext.clear();
        return obj;
    }

    public static com.example.locationtrack.Location copyOrUpdate(Realm realm, LocationColumnInfo columnInfo, com.example.locationtrack.Location object, boolean update, Map<RealmModel,RealmObjectProxy> cache, Set<ImportFlag> flags) {
        if (object instanceof RealmObjectProxy && !RealmObject.isFrozen(object) && ((RealmObjectProxy) object).realmGet$proxyState().getRealm$realm() != null) {
            final BaseRealm otherRealm = ((RealmObjectProxy) object).realmGet$proxyState().getRealm$realm();
            if (otherRealm.threadId != realm.threadId) {
                throw new IllegalArgumentException("Objects which belong to Realm instances in other threads cannot be copied into this Realm instance.");
            }
            if (otherRealm.getPath().equals(realm.getPath())) {
                return object;
            }
        }
        final BaseRealm.RealmObjectContext objectContext = BaseRealm.objectContext.get();
        RealmObjectProxy cachedRealmObject = cache.get(object);
        if (cachedRealmObject != null) {
            return (com.example.locationtrack.Location) cachedRealmObject;
        }

        com.example.locationtrack.Location realmObject = null;
        boolean canUpdate = update;
        if (canUpdate) {
            Table table = realm.getTable(com.example.locationtrack.Location.class);
            long pkColumnKey = columnInfo._idColKey;
            org.bson.types.ObjectId value = ((com_example_locationtrack_LocationRealmProxyInterface) object).realmGet$_id();
            long objKey = Table.NO_MATCH;
            if (value == null) {
                objKey = table.findFirstNull(pkColumnKey);
            } else {
                objKey = table.findFirstObjectId(pkColumnKey, value);
            }
            if (objKey == Table.NO_MATCH) {
                canUpdate = false;
            } else {
                try {
                    objectContext.set(realm, table.getUncheckedRow(objKey), columnInfo, false, Collections.<String> emptyList());
                    realmObject = new io.realm.com_example_locationtrack_LocationRealmProxy();
                    cache.put(object, (RealmObjectProxy) realmObject);
                } finally {
                    objectContext.clear();
                }
            }
        }

        return (canUpdate) ? update(realm, columnInfo, realmObject, object, cache, flags) : copy(realm, columnInfo, object, update, cache, flags);
    }

    public static com.example.locationtrack.Location copy(Realm realm, LocationColumnInfo columnInfo, com.example.locationtrack.Location newObject, boolean update, Map<RealmModel,RealmObjectProxy> cache, Set<ImportFlag> flags) {
        RealmObjectProxy cachedRealmObject = cache.get(newObject);
        if (cachedRealmObject != null) {
            return (com.example.locationtrack.Location) cachedRealmObject;
        }

        com_example_locationtrack_LocationRealmProxyInterface unmanagedSource = (com_example_locationtrack_LocationRealmProxyInterface) newObject;

        Table table = realm.getTable(com.example.locationtrack.Location.class);
        OsObjectBuilder builder = new OsObjectBuilder(table, flags);

        // Add all non-"object reference" fields
        builder.addObjectId(columnInfo._idColKey, unmanagedSource.realmGet$_id());
        builder.addString(columnInfo._partitionColKey, unmanagedSource.realmGet$_partition());
        builder.addFloat(columnInfo.accuracyColKey, unmanagedSource.realmGet$accuracy());
        builder.addDouble(columnInfo.latitudeColKey, unmanagedSource.realmGet$latitude());
        builder.addDouble(columnInfo.longitudeColKey, unmanagedSource.realmGet$longitude());
        builder.addFloat(columnInfo.speedColKey, unmanagedSource.realmGet$speed());
        builder.addInteger(columnInfo.timeColKey, unmanagedSource.realmGet$time());
        builder.addDouble(columnInfo.altitudeColKey, unmanagedSource.realmGet$altitude());

        // Create the underlying object and cache it before setting any object/objectlist references
        // This will allow us to break any circular dependencies by using the object cache.
        Row row = builder.createNewObject();
        io.realm.com_example_locationtrack_LocationRealmProxy managedCopy = newProxyInstance(realm, row);
        cache.put(newObject, managedCopy);

        return managedCopy;
    }

    public static long insert(Realm realm, com.example.locationtrack.Location object, Map<RealmModel,Long> cache) {
        if (object instanceof RealmObjectProxy && !RealmObject.isFrozen(object) && ((RealmObjectProxy) object).realmGet$proxyState().getRealm$realm() != null && ((RealmObjectProxy) object).realmGet$proxyState().getRealm$realm().getPath().equals(realm.getPath())) {
            return ((RealmObjectProxy) object).realmGet$proxyState().getRow$realm().getObjectKey();
        }
        Table table = realm.getTable(com.example.locationtrack.Location.class);
        long tableNativePtr = table.getNativePtr();
        LocationColumnInfo columnInfo = (LocationColumnInfo) realm.getSchema().getColumnInfo(com.example.locationtrack.Location.class);
        long pkColumnKey = columnInfo._idColKey;
        org.bson.types.ObjectId primaryKeyValue = ((com_example_locationtrack_LocationRealmProxyInterface) object).realmGet$_id();
        long objKey = Table.NO_MATCH;
        if (primaryKeyValue == null) {
            objKey = Table.nativeFindFirstNull(tableNativePtr, pkColumnKey);
        } else {
            objKey = Table.nativeFindFirstObjectId(tableNativePtr, pkColumnKey, primaryKeyValue.toString());
        }
        if (objKey == Table.NO_MATCH) {
            objKey = OsObject.createRowWithPrimaryKey(table, pkColumnKey, primaryKeyValue);
        } else {
            Table.throwDuplicatePrimaryKeyException(primaryKeyValue);
        }
        cache.put(object, objKey);
        String realmGet$_partition = ((com_example_locationtrack_LocationRealmProxyInterface) object).realmGet$_partition();
        if (realmGet$_partition != null) {
            Table.nativeSetString(tableNativePtr, columnInfo._partitionColKey, objKey, realmGet$_partition, false);
        }
        Table.nativeSetFloat(tableNativePtr, columnInfo.accuracyColKey, objKey, ((com_example_locationtrack_LocationRealmProxyInterface) object).realmGet$accuracy(), false);
        Table.nativeSetDouble(tableNativePtr, columnInfo.latitudeColKey, objKey, ((com_example_locationtrack_LocationRealmProxyInterface) object).realmGet$latitude(), false);
        Table.nativeSetDouble(tableNativePtr, columnInfo.longitudeColKey, objKey, ((com_example_locationtrack_LocationRealmProxyInterface) object).realmGet$longitude(), false);
        Table.nativeSetFloat(tableNativePtr, columnInfo.speedColKey, objKey, ((com_example_locationtrack_LocationRealmProxyInterface) object).realmGet$speed(), false);
        Table.nativeSetLong(tableNativePtr, columnInfo.timeColKey, objKey, ((com_example_locationtrack_LocationRealmProxyInterface) object).realmGet$time(), false);
        Table.nativeSetDouble(tableNativePtr, columnInfo.altitudeColKey, objKey, ((com_example_locationtrack_LocationRealmProxyInterface) object).realmGet$altitude(), false);
        return objKey;
    }

    public static void insert(Realm realm, Iterator<? extends RealmModel> objects, Map<RealmModel,Long> cache) {
        Table table = realm.getTable(com.example.locationtrack.Location.class);
        long tableNativePtr = table.getNativePtr();
        LocationColumnInfo columnInfo = (LocationColumnInfo) realm.getSchema().getColumnInfo(com.example.locationtrack.Location.class);
        long pkColumnKey = columnInfo._idColKey;
        com.example.locationtrack.Location object = null;
        while (objects.hasNext()) {
            object = (com.example.locationtrack.Location) objects.next();
            if (cache.containsKey(object)) {
                continue;
            }
            if (object instanceof RealmObjectProxy && !RealmObject.isFrozen(object) && ((RealmObjectProxy) object).realmGet$proxyState().getRealm$realm() != null && ((RealmObjectProxy) object).realmGet$proxyState().getRealm$realm().getPath().equals(realm.getPath())) {
                cache.put(object, ((RealmObjectProxy) object).realmGet$proxyState().getRow$realm().getObjectKey());
                continue;
            }
            org.bson.types.ObjectId primaryKeyValue = ((com_example_locationtrack_LocationRealmProxyInterface) object).realmGet$_id();
            long objKey = Table.NO_MATCH;
            if (primaryKeyValue == null) {
                objKey = Table.nativeFindFirstNull(tableNativePtr, pkColumnKey);
            } else {
                objKey = Table.nativeFindFirstObjectId(tableNativePtr, pkColumnKey, primaryKeyValue.toString());
            }
            if (objKey == Table.NO_MATCH) {
                objKey = OsObject.createRowWithPrimaryKey(table, pkColumnKey, primaryKeyValue);
            } else {
                Table.throwDuplicatePrimaryKeyException(primaryKeyValue);
            }
            cache.put(object, objKey);
            String realmGet$_partition = ((com_example_locationtrack_LocationRealmProxyInterface) object).realmGet$_partition();
            if (realmGet$_partition != null) {
                Table.nativeSetString(tableNativePtr, columnInfo._partitionColKey, objKey, realmGet$_partition, false);
            }
            Table.nativeSetFloat(tableNativePtr, columnInfo.accuracyColKey, objKey, ((com_example_locationtrack_LocationRealmProxyInterface) object).realmGet$accuracy(), false);
            Table.nativeSetDouble(tableNativePtr, columnInfo.latitudeColKey, objKey, ((com_example_locationtrack_LocationRealmProxyInterface) object).realmGet$latitude(), false);
            Table.nativeSetDouble(tableNativePtr, columnInfo.longitudeColKey, objKey, ((com_example_locationtrack_LocationRealmProxyInterface) object).realmGet$longitude(), false);
            Table.nativeSetFloat(tableNativePtr, columnInfo.speedColKey, objKey, ((com_example_locationtrack_LocationRealmProxyInterface) object).realmGet$speed(), false);
            Table.nativeSetLong(tableNativePtr, columnInfo.timeColKey, objKey, ((com_example_locationtrack_LocationRealmProxyInterface) object).realmGet$time(), false);
            Table.nativeSetDouble(tableNativePtr, columnInfo.altitudeColKey, objKey, ((com_example_locationtrack_LocationRealmProxyInterface) object).realmGet$altitude(), false);
        }
    }

    public static long insertOrUpdate(Realm realm, com.example.locationtrack.Location object, Map<RealmModel,Long> cache) {
        if (object instanceof RealmObjectProxy && !RealmObject.isFrozen(object) && ((RealmObjectProxy) object).realmGet$proxyState().getRealm$realm() != null && ((RealmObjectProxy) object).realmGet$proxyState().getRealm$realm().getPath().equals(realm.getPath())) {
            return ((RealmObjectProxy) object).realmGet$proxyState().getRow$realm().getObjectKey();
        }
        Table table = realm.getTable(com.example.locationtrack.Location.class);
        long tableNativePtr = table.getNativePtr();
        LocationColumnInfo columnInfo = (LocationColumnInfo) realm.getSchema().getColumnInfo(com.example.locationtrack.Location.class);
        long pkColumnKey = columnInfo._idColKey;
        org.bson.types.ObjectId primaryKeyValue = ((com_example_locationtrack_LocationRealmProxyInterface) object).realmGet$_id();
        long objKey = Table.NO_MATCH;
        if (primaryKeyValue == null) {
            objKey = Table.nativeFindFirstNull(tableNativePtr, pkColumnKey);
        } else {
            objKey = Table.nativeFindFirstObjectId(tableNativePtr, pkColumnKey, primaryKeyValue.toString());
        }
        if (objKey == Table.NO_MATCH) {
            objKey = OsObject.createRowWithPrimaryKey(table, pkColumnKey, primaryKeyValue);
        }
        cache.put(object, objKey);
        String realmGet$_partition = ((com_example_locationtrack_LocationRealmProxyInterface) object).realmGet$_partition();
        if (realmGet$_partition != null) {
            Table.nativeSetString(tableNativePtr, columnInfo._partitionColKey, objKey, realmGet$_partition, false);
        } else {
            Table.nativeSetNull(tableNativePtr, columnInfo._partitionColKey, objKey, false);
        }
        Table.nativeSetFloat(tableNativePtr, columnInfo.accuracyColKey, objKey, ((com_example_locationtrack_LocationRealmProxyInterface) object).realmGet$accuracy(), false);
        Table.nativeSetDouble(tableNativePtr, columnInfo.latitudeColKey, objKey, ((com_example_locationtrack_LocationRealmProxyInterface) object).realmGet$latitude(), false);
        Table.nativeSetDouble(tableNativePtr, columnInfo.longitudeColKey, objKey, ((com_example_locationtrack_LocationRealmProxyInterface) object).realmGet$longitude(), false);
        Table.nativeSetFloat(tableNativePtr, columnInfo.speedColKey, objKey, ((com_example_locationtrack_LocationRealmProxyInterface) object).realmGet$speed(), false);
        Table.nativeSetLong(tableNativePtr, columnInfo.timeColKey, objKey, ((com_example_locationtrack_LocationRealmProxyInterface) object).realmGet$time(), false);
        Table.nativeSetDouble(tableNativePtr, columnInfo.altitudeColKey, objKey, ((com_example_locationtrack_LocationRealmProxyInterface) object).realmGet$altitude(), false);
        return objKey;
    }

    public static void insertOrUpdate(Realm realm, Iterator<? extends RealmModel> objects, Map<RealmModel,Long> cache) {
        Table table = realm.getTable(com.example.locationtrack.Location.class);
        long tableNativePtr = table.getNativePtr();
        LocationColumnInfo columnInfo = (LocationColumnInfo) realm.getSchema().getColumnInfo(com.example.locationtrack.Location.class);
        long pkColumnKey = columnInfo._idColKey;
        com.example.locationtrack.Location object = null;
        while (objects.hasNext()) {
            object = (com.example.locationtrack.Location) objects.next();
            if (cache.containsKey(object)) {
                continue;
            }
            if (object instanceof RealmObjectProxy && !RealmObject.isFrozen(object) && ((RealmObjectProxy) object).realmGet$proxyState().getRealm$realm() != null && ((RealmObjectProxy) object).realmGet$proxyState().getRealm$realm().getPath().equals(realm.getPath())) {
                cache.put(object, ((RealmObjectProxy) object).realmGet$proxyState().getRow$realm().getObjectKey());
                continue;
            }
            org.bson.types.ObjectId primaryKeyValue = ((com_example_locationtrack_LocationRealmProxyInterface) object).realmGet$_id();
            long objKey = Table.NO_MATCH;
            if (primaryKeyValue == null) {
                objKey = Table.nativeFindFirstNull(tableNativePtr, pkColumnKey);
            } else {
                objKey = Table.nativeFindFirstObjectId(tableNativePtr, pkColumnKey, primaryKeyValue.toString());
            }
            if (objKey == Table.NO_MATCH) {
                objKey = OsObject.createRowWithPrimaryKey(table, pkColumnKey, primaryKeyValue);
            }
            cache.put(object, objKey);
            String realmGet$_partition = ((com_example_locationtrack_LocationRealmProxyInterface) object).realmGet$_partition();
            if (realmGet$_partition != null) {
                Table.nativeSetString(tableNativePtr, columnInfo._partitionColKey, objKey, realmGet$_partition, false);
            } else {
                Table.nativeSetNull(tableNativePtr, columnInfo._partitionColKey, objKey, false);
            }
            Table.nativeSetFloat(tableNativePtr, columnInfo.accuracyColKey, objKey, ((com_example_locationtrack_LocationRealmProxyInterface) object).realmGet$accuracy(), false);
            Table.nativeSetDouble(tableNativePtr, columnInfo.latitudeColKey, objKey, ((com_example_locationtrack_LocationRealmProxyInterface) object).realmGet$latitude(), false);
            Table.nativeSetDouble(tableNativePtr, columnInfo.longitudeColKey, objKey, ((com_example_locationtrack_LocationRealmProxyInterface) object).realmGet$longitude(), false);
            Table.nativeSetFloat(tableNativePtr, columnInfo.speedColKey, objKey, ((com_example_locationtrack_LocationRealmProxyInterface) object).realmGet$speed(), false);
            Table.nativeSetLong(tableNativePtr, columnInfo.timeColKey, objKey, ((com_example_locationtrack_LocationRealmProxyInterface) object).realmGet$time(), false);
            Table.nativeSetDouble(tableNativePtr, columnInfo.altitudeColKey, objKey, ((com_example_locationtrack_LocationRealmProxyInterface) object).realmGet$altitude(), false);
        }
    }

    public static com.example.locationtrack.Location createDetachedCopy(com.example.locationtrack.Location realmObject, int currentDepth, int maxDepth, Map<RealmModel, CacheData<RealmModel>> cache) {
        if (currentDepth > maxDepth || realmObject == null) {
            return null;
        }
        CacheData<RealmModel> cachedObject = cache.get(realmObject);
        com.example.locationtrack.Location unmanagedObject;
        if (cachedObject == null) {
            unmanagedObject = new com.example.locationtrack.Location();
            cache.put(realmObject, new RealmObjectProxy.CacheData<RealmModel>(currentDepth, unmanagedObject));
        } else {
            // Reuse cached object or recreate it because it was encountered at a lower depth.
            if (currentDepth >= cachedObject.minDepth) {
                return (com.example.locationtrack.Location) cachedObject.object;
            }
            unmanagedObject = (com.example.locationtrack.Location) cachedObject.object;
            cachedObject.minDepth = currentDepth;
        }
        com_example_locationtrack_LocationRealmProxyInterface unmanagedCopy = (com_example_locationtrack_LocationRealmProxyInterface) unmanagedObject;
        com_example_locationtrack_LocationRealmProxyInterface realmSource = (com_example_locationtrack_LocationRealmProxyInterface) realmObject;
        Realm objectRealm = (Realm) ((RealmObjectProxy) realmObject).realmGet$proxyState().getRealm$realm();
        unmanagedCopy.realmSet$_id(realmSource.realmGet$_id());
        unmanagedCopy.realmSet$_partition(realmSource.realmGet$_partition());
        unmanagedCopy.realmSet$accuracy(realmSource.realmGet$accuracy());
        unmanagedCopy.realmSet$latitude(realmSource.realmGet$latitude());
        unmanagedCopy.realmSet$longitude(realmSource.realmGet$longitude());
        unmanagedCopy.realmSet$speed(realmSource.realmGet$speed());
        unmanagedCopy.realmSet$time(realmSource.realmGet$time());
        unmanagedCopy.realmSet$altitude(realmSource.realmGet$altitude());

        return unmanagedObject;
    }

    static com.example.locationtrack.Location update(Realm realm, LocationColumnInfo columnInfo, com.example.locationtrack.Location realmObject, com.example.locationtrack.Location newObject, Map<RealmModel, RealmObjectProxy> cache, Set<ImportFlag> flags) {
        com_example_locationtrack_LocationRealmProxyInterface realmObjectTarget = (com_example_locationtrack_LocationRealmProxyInterface) realmObject;
        com_example_locationtrack_LocationRealmProxyInterface realmObjectSource = (com_example_locationtrack_LocationRealmProxyInterface) newObject;
        Table table = realm.getTable(com.example.locationtrack.Location.class);
        OsObjectBuilder builder = new OsObjectBuilder(table, flags);
        builder.addObjectId(columnInfo._idColKey, realmObjectSource.realmGet$_id());
        builder.addString(columnInfo._partitionColKey, realmObjectSource.realmGet$_partition());
        builder.addFloat(columnInfo.accuracyColKey, realmObjectSource.realmGet$accuracy());
        builder.addDouble(columnInfo.latitudeColKey, realmObjectSource.realmGet$latitude());
        builder.addDouble(columnInfo.longitudeColKey, realmObjectSource.realmGet$longitude());
        builder.addFloat(columnInfo.speedColKey, realmObjectSource.realmGet$speed());
        builder.addInteger(columnInfo.timeColKey, realmObjectSource.realmGet$time());
        builder.addDouble(columnInfo.altitudeColKey, realmObjectSource.realmGet$altitude());

        builder.updateExistingTopLevelObject();
        return realmObject;
    }

    @Override
    @SuppressWarnings("ArrayToString")
    public String toString() {
        if (!RealmObject.isValid(this)) {
            return "Invalid object";
        }
        StringBuilder stringBuilder = new StringBuilder("Location = proxy[");
        stringBuilder.append("{_id:");
        stringBuilder.append(realmGet$_id() != null ? realmGet$_id() : "null");
        stringBuilder.append("}");
        stringBuilder.append(",");
        stringBuilder.append("{_partition:");
        stringBuilder.append(realmGet$_partition());
        stringBuilder.append("}");
        stringBuilder.append(",");
        stringBuilder.append("{accuracy:");
        stringBuilder.append(realmGet$accuracy());
        stringBuilder.append("}");
        stringBuilder.append(",");
        stringBuilder.append("{latitude:");
        stringBuilder.append(realmGet$latitude());
        stringBuilder.append("}");
        stringBuilder.append(",");
        stringBuilder.append("{longitude:");
        stringBuilder.append(realmGet$longitude());
        stringBuilder.append("}");
        stringBuilder.append(",");
        stringBuilder.append("{speed:");
        stringBuilder.append(realmGet$speed());
        stringBuilder.append("}");
        stringBuilder.append(",");
        stringBuilder.append("{time:");
        stringBuilder.append(realmGet$time());
        stringBuilder.append("}");
        stringBuilder.append(",");
        stringBuilder.append("{altitude:");
        stringBuilder.append(realmGet$altitude());
        stringBuilder.append("}");
        stringBuilder.append("]");
        return stringBuilder.toString();
    }

    @Override
    public ProxyState<?> realmGet$proxyState() {
        return proxyState;
    }

    @Override
    public int hashCode() {
        String realmName = proxyState.getRealm$realm().getPath();
        String tableName = proxyState.getRow$realm().getTable().getName();
        long objKey = proxyState.getRow$realm().getObjectKey();

        int result = 17;
        result = 31 * result + ((realmName != null) ? realmName.hashCode() : 0);
        result = 31 * result + ((tableName != null) ? tableName.hashCode() : 0);
        result = 31 * result + (int) (objKey ^ (objKey >>> 32));
        return result;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        com_example_locationtrack_LocationRealmProxy aLocation = (com_example_locationtrack_LocationRealmProxy)o;

        BaseRealm realm = proxyState.getRealm$realm();
        BaseRealm otherRealm = aLocation.proxyState.getRealm$realm();
        String path = realm.getPath();
        String otherPath = otherRealm.getPath();
        if (path != null ? !path.equals(otherPath) : otherPath != null) return false;
        if (realm.isFrozen() != otherRealm.isFrozen()) return false;
        if (!realm.sharedRealm.getVersionID().equals(otherRealm.sharedRealm.getVersionID())) {
            return false;
        }

        String tableName = proxyState.getRow$realm().getTable().getName();
        String otherTableName = aLocation.proxyState.getRow$realm().getTable().getName();
        if (tableName != null ? !tableName.equals(otherTableName) : otherTableName != null) return false;

        if (proxyState.getRow$realm().getObjectKey() != aLocation.proxyState.getRow$realm().getObjectKey()) return false;

        return true;
    }
}
