diff --git a/partition.cpp b/partition.cpp
index 9012d49..8d86f69 100644
--- a/partition.cpp
+++ b/partition.cpp
@@ -1528,10 +1528,23 @@
 		string Command = "mount -o bind '" + Symlink_Path + "' '" + Symlink_Mount_Point + "'";
 		TWFunc::Exec_Cmd(Command);
 	}
+
+	if (Mount_Point == "/system_root") {
+		unlink("/system");
+		mkdir("/system", 0755);
+		mount("/system_root/system", "/system", "auto", MS_BIND, NULL);
+	}
+
 	return true;
 }
 
 bool TWPartition::UnMount(bool Display_Error) {
+	if (Mount_Point == "/system_root") {
+		if (umount("/system") == -1)
+			umount2("/system", MNT_DETACH);
+		rmdir("/system");
+		symlink("/system_root/system", "/system");
+	}
 	if (Is_Mounted()) {
 		int never_unmount_system;
 
