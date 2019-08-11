// #[cfg(test)]
// mod tests {
//     #[test]
//     fn it_works() {
//         assert_eq!(2 + 2, 4);
//     }
// }

// #[crate_type = "lib"]
// #[no_std]
// #[allow(ctypes)]

#[no_mangle]
pub extern "C" fn hello_world_in_rust() {
    println!("Hello World, Rust here!");
}