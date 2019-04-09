// #[cfg(test)]
// mod tests {
//     #[test]
//     fn it_works() {
//         assert_eq!(2 + 2, 4);
//     }
// }

#[no_mangle]
pub unsafe extern "C" fn hello_world_in_rust() {
    println!("Hello World, Rust here!");
}