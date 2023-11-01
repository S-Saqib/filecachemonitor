scp ssaqib@128.105.145.95:/filecachemonitor/server_cached_pages.txt .
mv ./server_cached_pages.txt ./server0_cached_pages.txt

scp ssaqib@128.105.145.84:/filecachemonitor/server_cached_pages.txt .
mv ./server_cached_pages.txt ./server1_cached_pages.txt

scp ssaqib@128.105.145.93:/filecachemonitor/server_cached_pages.txt .
mv ./server_cached_pages.txt ./server2_cached_pages.txt

scp ssaqib@128.105.144.226:/filecachemonitor/client_cached_pages.txt .

python compare_caches.py
